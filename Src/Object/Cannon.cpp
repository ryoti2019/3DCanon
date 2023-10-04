#include <DxLib.h>
#include "../Utility/Application.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "../Object/ShotBase.h"
#include"../Scene/GameScene.h"
#include "ShotNomal.h"
#include "ShotSpecial.h"
#include "EnemyBase.h"
#include "Cannon.h"

Cannon::Cannon(void)
{
}

Cannon::~Cannon(void)
{
}

void Cannon::Init(GameScene* scene)
{

	gameScene_ = scene;

#pragma region 砲台

	// 外部ファイルの砲台３Ｄモデルをロード
	standModelId_ = MV1LoadModel(
		(Application::PATH_MODEL + "Cannon/Stand.mv1").c_str());

	//砲台の大きさ
	standScl_ = { 0.8f, 0.8f, 0.8f };

	// 砲台の角度
	standRot_ = { 0.0f, 0.0f, 0.0f };

	// 砲台の位置
	standPos_ = { 0.0f, 10.0f, -200.0f };

#pragma endregion

#pragma region 砲身

	// 外部ファイルの砲身３Ｄモデルをロード
	barrelModelId_ = MV1LoadModel(
		(Application::PATH_MODEL + "Cannon/Barrel.mv1").c_str());

	// 砲身の大きさ
	barrelScl_ = { 0.8f, 0.8f, 0.8f };

	// 砲身の角度
	barrelRot_ = { 0.0f, 0.0f, 0.0f };

	// 砲身の位置
	barrelPos_ = { 0.0f, 110.0f, -200.0f };

	// 砲台からの相対座標
	barrelLocalPos_ = { 0.0f, 100.0f, 0.0f };

	//barrelPos_ = standPos_ + barrelLocalPos_;
	barrelPos_ = VAdd(standPos_, barrelLocalPos_);

#pragma endregion

	shotModelId_[0] = MV1LoadModel((Application::PATH_MODEL + "Cannon/Shot.mv1").c_str());
	shotModelId_[1] = MV1LoadModel((Application::PATH_MODEL + "Cannon/Shot.mv1").c_str());

	// 弾発射の硬直時間
	stepShotDelay_ = 0.0f;

	// 爆発エフェクト読み込み
	LoadDivGraph((Application::PATH_IMAGE + "Blast.png").c_str(),
		BLAST_ANIM_NUM, 4, 4, BLAST_SIZE_X, BLAST_SIZE_Y, blastImgs_, true);

	// 3Dモデルに制御情報を反映させるため
	Update();

}

void Cannon::Update(void)
{

	// 砲台の回転
	ProcessRot();

	// 弾の発射
	ProcessShot();

	// 弾の種類の選択
	Shot();

	// 砲身
	MV1SetRotationXYZ(barrelModelId_, barrelRot_);
	MV1SetScale(barrelModelId_, barrelScl_);
	MV1SetPosition(barrelModelId_, barrelPos_);

	// 砲台
	MV1SetRotationXYZ(standModelId_, standRot_);
	MV1SetPosition(standModelId_, standPos_);
	MV1SetScale(standModelId_, standScl_);

}

void Cannon::Draw(void)
{
	// ロードされた３Ｄモデルを画面に描画
	MV1DrawModel(standModelId_);
	MV1DrawModel(barrelModelId_);

	// 弾の発射位置
	VECTOR pos = barrelPos_;

	// 砲身からの相対座標
	VECTOR localPos = { 0.0f, 25.0f, 30.0f };

	// 砲身の回転行列
	MATRIX matRot = MGetIdent();
	matRot = MMult(matRot, MGetRotX(barrelRot_.x));
	matRot = MMult(matRot, MGetRotY(barrelRot_.y));
	matRot = MMult(matRot, MGetRotZ(barrelRot_.z));

	// 方向と同じ要領で、相対座標を回転
	VECTOR localPosRot = VTransform(localPos, matRot);

	// ローカル座標からワールド座標へ変換
	pos = VAdd(pos, localPosRot);

	// 弾の発射位置目安
	DrawSphere3D(pos, 10.0f, 10, 0x00ff00, 0x00ff00, true);

	// 砲台のモデル描画
	MV1DrawModel(standModelId_);

	// 砲身のモデル描画(一時的に半透明にする)
	MV1SetMaterialDifColor(barrelModelId_, 0, GetColorF(1.0f, 1.0f, 1.0f, 0.25f));
	MV1DrawModel(barrelModelId_);

	if (mode_ == ShotMode::Normal)
	{
		DrawFormatString(0, 600, 0xffffff, "Normal");
	}

	if (mode_ == ShotMode::Special)
	{
		DrawFormatString(0, 600, 0xffffff, "Special");
	}

}

void Cannon::Release(void)
{
	// ロードされた３Ｄモデルをメモリから解放
	MV1DeleteModel(standModelId_);
	MV1DeleteModel(barrelModelId_);
	MV1DeleteModel(shotModelId_[0]);
	MV1DeleteModel(shotModelId_[1]);

	for (auto shot : shots_)
	{
		shot->Release();
		delete shot;
	}

	// 読み込んだ画像の解放
	for (int i = 0; i < BLAST_ANIM_NUM; i++)
	{
		DeleteGraph(blastImgs_[i]);
	}
}

std::vector<ShotBase*> Cannon::GetShots(void)
{
	return shots_;
}

void Cannon::ProcessRot(void)
{

	auto& ins = InputManager::GetInstance();
	float rotPow = 1.0f * DX_PI_F / 180.0f;

	//　縦回転
	if (ins.IsNew(KEY_INPUT_DOWN)) 
	{
		barrelRot_.x += rotPow;
	}

	if (ins.IsNew(KEY_INPUT_UP))
	{ 
		barrelRot_.x -= rotPow;
	}

	// 横回転(砲身のY軸回転)
	if (ins.IsNew(KEY_INPUT_RIGHT))
	{ 
		standRot_.y += rotPow;
		barrelRot_.y += rotPow; 
	}

	if (ins.IsNew(KEY_INPUT_LEFT)) 
	{ 
		standRot_.y -= rotPow;
		barrelRot_.y -= rotPow;
	};

	// 角度制限
	if (MAX_ANGLE_X < barrelRot_.x) { barrelRot_.x = MAX_ANGLE_X; }
	if (MIN_ANGLE_X > barrelRot_.x) { barrelRot_.x = MIN_ANGLE_X; }


}

void Cannon::ProcessShot(void)
{

	auto& ins = InputManager::GetInstance();
	// 攻撃キーを押すと、弾を生成
	if (ins.IsNew(KEY_INPUT_Z) && stepShotDelay_ <= 0.0f)
	{

		// 有効な弾を取得する
		ShotBase* shot = GetValidShot();

		// 単位行列(無回転の状態) 単位行列
		MATRIX matRot = MGetIdent();

		// それぞれの軸の行列を作り、更に行列を合成していく
		matRot = MMult(matRot, MGetRotX(barrelRot_.x));
		matRot = MMult(matRot, MGetRotY(barrelRot_.y));
		matRot = MMult(matRot, MGetRotZ(barrelRot_.z));

		// 弾の発射位置
		VECTOR pos = barrelPos_;

		// 砲身からの相対座標
		VECTOR localPos = { 0.0f, 25.0f, 30.0f };

		// 方向と同じ要領で、相対座標を回転
		VECTOR localPosRot = VTransform(localPos, matRot);

		// ローカル座標からワールド座標へ変換
		pos = VAdd(pos, localPosRot);

		// 回転行列を使用して、ベクトルを回転させる
		VECTOR dir = VTransform({ 0.0f, 0.0f, 1.0f }, matRot);

		// 弾を生成(方向は仮で正面方向)
		shot->CreateShot(pos, dir);

		// 弾発射後の硬直時間セット
		stepShotDelay_ = SHOT_DELAY;

	}

	// 弾発射後の硬直時間を減らしていく
	if (stepShotDelay_ > 0.0f)
	{
		stepShotDelay_ -= 1.0f / SceneManager::DEFAULT_FPS;
	}

}

ShotBase* Cannon::GetValidShot(void)
{

	size_t size = shots_.size();
	for (int i = 0; i < size; i++)
	{
		// 後から修正するかも
		if (!shots_[i]->IsShot() && static_cast<int>(shots_[i]->GetShotType()) == static_cast<int>(mode_))
		{
			return shots_[i];
		}
	}

	// 弾の生成
	ShotBase* shot = nullptr;
	switch (mode_)
	{
	case ShotMode::Normal:
		shot = new ShotNormal(shotModelId_[0], blastImgs_, BLAST_ANIM_NUM);
		break;
	case ShotMode::Special:
		shot = new ShotSpecial(shotModelId_[1], blastImgs_, BLAST_ANIM_NUM);
		break;
	}

	shots_.push_back(shot);

	return shot;

}

void Cannon::Shot(void)
{

	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_X) && gameScene_->GetSpecialShot())
	{
		if (mode_ == ShotMode::Normal)
		{
			mode_ = ShotMode::Special;
			return;
		}

		if (mode_ == ShotMode::Special)
		{
			mode_ = ShotMode::Normal;
			return;
		}

	}



}
