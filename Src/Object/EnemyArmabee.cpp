#include "../Manager/SceneManager.h"
#include "EnemyArmabee.h"

EnemyArmabee::EnemyArmabee(int baseModelId) : EnemyBase(baseModelId)
{
}

void EnemyArmabee::SetParam(void)
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
    speed_ = 0.5f;

    // 初期は生存状態
    isAlive_ = true;

    // アニメーションをアタッチする
    animAttachNo_ = MV1AttachAnim(modelId_, 2);

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

    // 移動用のフラグ
    up_ = false;
    down_ = false;

    count_ = 0;

}

void EnemyArmabee::Update(void)
{

    //※生存していけなければ、処理しない
    if (!isAlive_)
    {
        return;
    }

    //移動処理
    // 移動量の計算(方向×スピード)
    VECTOR movePow;
    movePow = VScale(dir_, speed_);
    pos_ = VAdd(pos_, movePow);

    if (count_ == 0)
    {
        up_ = true;
    }

    // 上に移動
    if (up_)
    {
        movePow = VScale({ 1.0f, 1.0f, 0.0f }, speed_);
        pos_ = VAdd(pos_, movePow);
    }

    if (count_ == 60)
    {
        down_ = true;
        up_ = false;
    }

    // 下に移動
    if (down_)
    {
        movePow = VScale({ 1.0f, -1.0f, 0.0f }, speed_);
        pos_ = VAdd(pos_, movePow);
        if (count_ == 120)
        {
            up_ = true;
            down_ = false;
            count_ = 0;
        }
       
    }

    // 移動した後の硬直時間
    count_++;

    // アニメーション再生
    // 経過時間の取得
    float deltaTime = 1.0f / SceneManager::DEFAULT_FPS;

    // アニメーション時間の進行
    stepAnim_ += (speedAnim_ * deltaTime);
    if (stepAnim_ > animTotalTime_)
    {
        // ループ再生
        stepAnim_ = 0.0f;
    }

    // 再生するアニメーション時間の設定
    MV1SetAttachAnimTime(modelId_, animAttachNo_, stepAnim_);

    //※大きさ、角度、座標の３Ｄ制御
    // 大きさの設定
    MV1SetScale(modelId_, scl_);

    // 角度の設定
    MV1SetRotationXYZ(modelId_, rot_);

    // 位置の設定
    MV1SetPosition(modelId_, pos_);

}


