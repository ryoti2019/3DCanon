#include "../Manager/SceneManager.h"
#include "ShotBase.h"

ShotBase::ShotBase(int baseModelId, int* blastImgs, int blastAnimNum)
{
	baseModelId_ = baseModelId;
	blastImgs_ = blastImgs;
	blastAnimNum_ = blastAnimNum;
}

ShotBase::~ShotBase(void)
{
}

void ShotBase::CreateShot(VECTOR pos, VECTOR dir)
{

}

void ShotBase::Update(void)
{
	// ①STATE実装

	switch (state_)
	{

	case ShotBase::STATE::SHOT:
		UpdateShot();
		break;
	case ShotBase::STATE::BLAST:
		UpdateBlast();
		break;
	case ShotBase::STATE::END:
		UpdateEnd();
		break;

	}

}

void ShotBase::UpdateShot(void)
{

	// 弾を移動させる

	// 移動量の計算(方向×スピード)
	VECTOR movePow;
	//movePow.x = dir_.x * speed_;
	//movePow.y = dir_.y * speed_;
	//movePow.z = dir_.z * speed_;
	movePow = VScale(dir_, speed_);

	// 移動処理(座標+移動量)
	//pos_.x += movePow.x;
	//pos_.y += movePow.y;
	//pos_.z += movePow.z;
	pos_ = VAdd(pos_, movePow);

	//pos_ = VAdd(pos_, VScale(dir_, speed_));

	// 更に加速度的に重力を加える
	gravityPow_ += SceneManager::GRAVITY / SceneManager::DEFAULT_FPS;

	// pos_.y -= gravityPow_;

	pos_ = VAdd(pos_, VScale({ 0.0f, -1.0f, 0.0f }, gravityPow_));

	// 大きさの設定
	MV1SetScale(modelId_, scl_);

	// 角度の設定
	MV1SetRotationXYZ(modelId_, rot_);

	// 位置の設定
	MV1SetPosition(modelId_, pos_);

}

void ShotBase::UpdateBlast(void)
{
	// 爆発アニメーション
	blastCntAnim_++;

	// 爆発のアニメーション番号
	blastIdxAnim_ = static_cast<int>(static_cast<float>(blastCntAnim_) * blastSpeedAnim_) % blastAnimNum_;

	// 爆発アニメーションの終了判定
	if (blastIdxAnim_ + 1 >= blastAnimNum_)
	{
		ChangeState(STATE::END);
	}

}

void ShotBase::UpdateEnd(void)
{
}

void ShotBase::Draw()
{
	// ③STATE実装

	switch (state_)
	{

	case ShotBase::STATE::SHOT:
		DrawShot();
		break;
	case ShotBase::STATE::BLAST:
		DrawBlast();
		break;
	case ShotBase::STATE::END:
		DrawEnd();
		break;

	}
}

void ShotBase::DrawShot()
{
	MV1DrawModel(modelId_);
}

void ShotBase::DrawBlast()
{
	// 2Dのアニメーション描画
	DrawBillboard3D(
		pos_, 0.5f, 0.5f, 80.0f, 0.0f, blastImgs_[blastIdxAnim_], true);
}

void ShotBase::DrawEnd()
{
}

void ShotBase::Release(void)
{
	//MV1DeleteModel(modelId_);
}

bool ShotBase::IsShot(void)
{
	//※STATEがSHOT状態だったらtrue
	return state_ == STATE::SHOT;
}

void ShotBase::ChangeState(STATE state)
{
	// 状態の更新
	state_ = state;

	// 状態遷移時の初期化
	switch (state_)
	{
	case ShotBase::STATE::SHOT:
		break;
	case ShotBase::STATE::BLAST:
		blastCntAnim_ = 0;
		break;
	case ShotBase::STATE::END:
		break;
	}
}

VECTOR ShotBase::GetPos()
{
	return pos_;
}

void ShotBase::Blast(void)
{
	//※BLAST状態へ遷移させる
	ChangeState(STATE::BLAST);
}

float ShotBase::GetCollisionRadius(void)
{
	return collisionRadius_;
}

ShotBase::TYPE ShotBase::GetShotType(void)
{
	return shotType_;
}
