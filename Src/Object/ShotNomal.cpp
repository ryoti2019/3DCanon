#include "ShotNomal.h"

ShotNormal::ShotNormal(int baseModelId, int* blastImgs, int blastAnimNum) : ShotBase(baseModelId,  blastImgs, blastAnimNum)
{
}

void ShotNormal::CreateShot(VECTOR pos, VECTOR dir)
{

	// 弾の種類
	shotType_ = TYPE::Normal;

	// 使用メモリ容量と読み込み時間の削減のため
	// モデルデータをいくつもメモリ上に存在させない
	modelId_ = MV1DuplicateModel(baseModelId_);

	// 弾の大きさを設定
	scl_ = { 0.8f, 0.8f, 0.8f };

	// 弾の角度を設定
	rot_ = { 0.0f, 0.0f, 0.0f };

	// 弾の発射位置を設定
	pos_ = pos;

	// 弾の発射方向の設定
	dir_ = dir;

	// 弾の半径
	collisionRadius_ = 10.0f;

	// 弾の速度
	speed_ = 8.0f;

	// 重力
	gravityPow_ = 0.0f;

	// 爆発のアニメーション用カウンタ
	blastCntAnim_ = 0;

	// 爆発のアニメーション速度
	blastSpeedAnim_ = 0.3f;

	// 状態の初期化
	state_ = STATE::NONE;

	// 衝突判定用の球体半径
	collisionRadius_ = 10.0f;

	// 状態遷移
	ChangeState(STATE::SHOT);

}
