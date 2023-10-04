#include "EnemyBirb.h"

EnemyBirb::EnemyBirb(int baseModelId) : EnemyBase(baseModelId)
{
}

void EnemyBirb::SetParam(void)
{

    // 使用メモリ容量と読み込み時間の削減のため
    // モデルデータをいくつもメモリ上に存在させない
    modelId_ = MV1DuplicateModel(baseModelId_);

    // 大きさの設定
    scl_ = { 0.3f, 0.3f, 0.3f };

    // 角度の設定
    rot_ = { 0.0f, -90.0f * DX_PI_F / 180.0f, 0.0f };

    // 位置の設定
    pos_ = { -350.0f, 30.0f, 75.0f };

    // 右方向に移動する
    dir_ = { 1.0f, 0.0f, 0.0f };

    // 移動スピード
    speed_ = 1.5f;

    // 初期は生存状態
    isAlive_ = true;

    // アニメーションをアタッチする
    animAttachNo_ = MV1AttachAnim(modelId_, 10);

    // アタッチしているアニメーションの総再生時間を取得する
    animTotalTime_ = MV1GetAttachAnimTotalTime(modelId_, animAttachNo_);

    // 再生中のアニメーション時間
    stepAnim_ = 0.0f;

    // アニメーション速度
    speedAnim_ = 30.0f;

    // HPの設定
    hp_ = hpMax_ = 2;

    // 衝突判定用の球体半径
    collisionRadius_ = 35.0f;

    // 衝突判定用の球体中心の調整座標
    collisionLocalPos_ = { 0.0f, 50.0f, 0.0f };

}
