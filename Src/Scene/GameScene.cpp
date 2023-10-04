#include <string>
#include <DxLib.h>
#include "../Utility/Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Object/Camera.h"
#include "../Object/Stage.h"
#include "../Object/Cannon.h"
#include "../Object/ShotBase.h"
#include "../Object/EnemyBase.h"
#include "../Object/EnemyBirb.h"
#include "../Object/EnemyArmabee.h"

#include "GameScene.h"

GameScene::GameScene(void)
{
}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
{

	// カメラ
	Camera* camera = SceneManager::GetInstance().Getcamera();
	camera->ChangeMode(Camera::MODE::FIXED_POINT);

	// ステージの初期化
	stage_ = new Stage(); 
	stage_->Init();

	// 砲台の初期化
	cannon_ = new Cannon();
	cannon_->Init(this);

	// カメラをフリーモードにする
	SceneManager::GetInstance().Getcamera()->ChangeMode(Camera::MODE::FREE);

	enemyModelId_[0] = MV1LoadModel((Application::PATH_MODEL + "Enemy/Birb.mv1").c_str());

	enemyModelId_[1] = MV1LoadModel((Application::PATH_MODEL + "Enemy/Armabee.mv1").c_str());

	// ゲームオーバー地点
	gameoverPoint_ = { 450.0f, 30.0f, 75.0f };

	// ゲームオーバー判定
	isGameover_ = false;

	// ゲームオーバー画像
	imgGameover_ =
		LoadGraph((Application::PATH_IMAGE + "Gameover.png").c_str());

	// ゲームクリア判定
	isGameclear_ = false;

	// ゲームクリア画像
	imgGameclear_ = LoadGraph((Application::PATH_IMAGE + "GameClear.png").c_str());

	// 敵が死んだ数
	deathEnemyCounter_ = 0;

	// スペシャルショットが打てるか
	specialShot_ = false;
	cnt_ = 0;

	// 一時的な描画領域
	tmpScreen_ = MakeScreen(Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, true);
}

void GameScene::Update(void)
{

	//if (isGameover_ || isGameclear_)
	//{
	//	// ゲームオーバーなら処理しない
	//	return;
	//}

	// ゲームオーバー判定
	for (auto enemy : enemys_)
	{
		if (AsoUtility::IsHitSpheres(
			enemy->GetCollisionPos(), enemy->GetCollisionRadius(),
			gameoverPoint_, 30.0f))
		{
			isGameover_ = true;
		}
	}

	//// ゲームクリア判定
	//for (auto enemy : enemys_)
	//{
	//	if (!enemy->IsAlive())
	//	{
	//		isGameclear_ = true;
	//	}
	//}

	// ステージの更新
	stage_->Update();

	// 砲台の更新
	cannon_->Update();

	// 敵の更新
	for (auto enemy : enemys_)
	{
		enemy->Update();
	}

	// 敵の初期化
	if (enCounter_ > ENCOUNT)
	{
		// エンカウントリセット
		enCounter_ = 0;

		// 敵の生成
		EnemyBase* enemy = nullptr;
		int eType = GetRand(static_cast<int>(EnemyBase::TYPE::MAX) - 1);
		EnemyBase::TYPE type = static_cast<EnemyBase::TYPE>(eType);
		switch (type)
		{
		case EnemyBase::TYPE::Birb:
			enemy = new EnemyBirb(enemyModelId_[0]);
			break;
		case EnemyBase::TYPE::Armabee:
			enemy = new EnemyArmabee(enemyModelId_[1]);
			break;
		}

		enemy->Init(this);
		enemys_.push_back(enemy);

	}
	enCounter_++;

	// ステージモデルID
	int stageModelId = stage_->GetModelId();

	// 弾の更新
	auto shots = cannon_->GetShots();
	for (auto shot : shots)
	{

		shot->Update();

		// 弾がSHOT状態じゃなかったら衝突判定しない
		if (!shot->IsShot())
		{
			// 爆発中や処理終了後は、以降の処理は実行しない
			continue;
		}

		// ステージモデルとの衝突判定
		auto info = MV1CollCheck_Sphere(
			stageModelId, -1, shot->GetPos(), shot->GetCollisionRadius());

		if (info.HitNum > 0)
		{
			// 衝突している
			shot->Blast();
		}

		// 当たり判定結果ポリゴン配列の後始末をする
		MV1CollResultPolyDimTerminate(info);

		// お互いの半径の合計
		//float radius = enemy->GetCollisionRadius() + shot->GetCollisionRadius();
		// 座標の差からお互いの距離を取る
		//VECTOR diff = VSub(enemy->GetCollisionPos(), shot->GetPos());
		// 三平方の定理で比較(SqrMagnitudeと同じ)
		//float dis = (diff.x * diff.x) + (diff.y * diff.y) + (diff.z * diff.z);
		// 球体と球体の衝突判定
		//if (dis < (radius * radius))
		//{
			// 敵にダメージを与える
			//enemy->Damage(1);
			//shot->Blast();
			//break;
		//}

		// 敵との衝突判定
		for (auto enemy : enemys_)
		{
			if (enemy->IsAlive())
			{
				if (AsoUtility::IsHitSpheres(
					enemy->GetCollisionPos(), enemy->GetCollisionRadius(),
					shot->GetPos(), shot->GetCollisionRadius()))
				{
					// 敵にダメージを与える
					enemy->Damage(1);
					shot->Blast();
					break;
				}
			}
		}
	}

	// ゲームオーバー判定
	for (auto enemy : enemys_)
	{
		// 球体と球体の衝突判定
		if (AsoUtility::IsHitSpheres(
			enemy->GetCollisionPos(), enemy->GetCollisionRadius(),
			gameoverPoint_, OVER_COL_RADIUS))
		{
			isGameover_ = true;
			break;
		}
	}

	//// シーン遷移
	//InputManager& ins = InputManager::GetInstance();
	//if (ins.IsTrgDown(KEY_INPUT_SPACE))
	//{
	//	SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
	//}

	// ３体敵を倒したらスペシャルショットが打てる
	if (deathEnemyCounter_ >= DEATH_ENEMY_MAX)
	{
		specialShot_ = true;
	}

	// 敵を5体倒したらクリア
	if (deathEnemyCounter_ >= 5)
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::CLEAR);
	}

}

void GameScene::Draw(void)
{

	//振動
	if (cnt_ > 0)
	{
		cnt_--;
		float s[5] = { -5.0f,2.5f,0.0f,-2.5f,5.0f };
		int shake = cnt_ % 5;

		SceneManager::GetInstance().Getcamera()->AddPos({ s[shake], s[shake], 0.0f});
		//DrawGraph(shake, shake, tmpScreen_, true);
		if (cnt_ <= 0)
		{
			SceneManager::GetInstance().Getcamera()->SetPos({ 3.0f, 275.0f, -450.0f });
			cnt_ = 0;
		}
	}

	// ステージの描画
	stage_->Draw();

	// 砲台の描画
	cannon_->Draw();

	// Y座標に少し加算
	VECTOR point = { 0.0f, 30.0f, 0.0f };

	// 敵の描画
	for (auto enemy : enemys_)
	{
		enemy->Draw();
		// ゲームオーバー地点の円の描画
		//DrawSphere3D(VAdd(gameoverPoint_, enemy->GetCollisionPos()), 10.0f, 10, 0xff0000, 0xff0000, false);
		//DrawSphere3D(VAdd(gameoverPoint_, point), 30.0f, 10, 0xff0000, 0xff0000, false);
	}

	// 弾の更新
	auto shots = cannon_->GetShots();
	for (auto shot : shots)
	{
		shot->Draw();

		DrawSphere3D(shot->GetPos(), shot->GetCollisionRadius(),
			10, 0xff0000, 0xff0000, false);

	}

	if (isGameover_)
	{
		// ゲームオーバー画像
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2,
					  Application::SCREEN_SIZE_Y / 2,
					  1.0f, 0.0f, imgGameover_, true);
	}

	if (isGameclear_)
	{
		// ゲームクリア画像
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2,
			Application::SCREEN_SIZE_Y / 2,
			1.0f, 0.0f, imgGameclear_, true);
	}

	// デバッグ用
	DrawSphere3D(gameoverPoint_, OVER_COL_RADIUS,
		10, 0xff0000, 0xff0000, false);

}

void GameScene::Release(void)
{

	// ステージの開放
	stage_->Release();

	// 砲台の開放
	cannon_->Release();

	// 敵の開放
	for (auto enemy : enemys_)
	{
		enemy->Release();
	}

	//// 弾の開放
	//auto shots = cannon_->GetShots();
	//for (auto shot : shots)
	//{
	//	shot->Release();
	//	//delete shot;
	//}

	// 敵のモデルの開放
	MV1DeleteModel(enemyModelId_[0]);
	MV1DeleteModel(enemyModelId_[1]);

	// ゲームオーバーの開放
	DeleteGraph(imgGameover_);

}

bool GameScene::GetSpecialShot(void)
{
	return specialShot_;
}

void GameScene::DeathEnemy(void)
{
	deathEnemyCounter_++;
}

void GameScene::CameraShake(int cnt)
{
	cnt_ = cnt;
}
