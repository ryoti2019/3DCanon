//#include "../Manager/SceneManager.h"
#include "../Scene/GameScene.h"
#include "EnemyBase.h"

EnemyBase::EnemyBase(int baseModelId)
{
    baseModelId_ = baseModelId;
}

EnemyBase::~EnemyBase(void)
{
}

void EnemyBase::Init(GameScene* scene)
{

    // ゲームシーンの取得
    gameScene_ = scene;

    // 敵のパラメータ設定
    SetParam();
    Update();

}

void EnemyBase::SetParam(void)
{
}

void EnemyBase::Update(void)
{

    //※生存していけなければ、処理しない
    if (!isAlive_)
    {
        return;
    }

    //※移動処理
    // 移動量の計算(方向×スピード)
    VECTOR movePow;
    movePow = VScale(dir_, speed_);
    pos_ = VAdd(pos_, movePow);

    // アニメーション再生
    // 経過時間の取得
    float deltaTime = 1.0f / 60.0f;

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

void EnemyBase::Draw(void)
{

    if (!isAlive_)
    {
        return;
    }

    MV1DrawModel(modelId_);

    // 敵の円の描画
    DrawSphere3D(VAdd(pos_, collisionLocalPos_), collisionRadius_, 10, 0xff0000, 0xff0000, false);

}

void EnemyBase::Release(void)
{
    MV1DeleteModel(modelId_);
}

VECTOR EnemyBase::GetPos(void)
{
    return pos_;
}

void EnemyBase::SetPos(VECTOR pos)
{
    pos_ = pos;
}

bool EnemyBase::IsAlive(void)
{
    return isAlive_;
}

void EnemyBase::SetAlive(bool alive)
{
    isAlive_ = alive;
}

void EnemyBase::Damage(int damage)
{

    hp_ -= damage;
    if (hp_ <= 0)
    {
        hp_ = 0;
        isAlive_ = false;
        gameScene_->DeathEnemy();
        gameScene_->CameraShake(30);
    }

}

VECTOR EnemyBase::GetCollisionPos(void)
{
    return VAdd(pos_, collisionLocalPos_);
}

float EnemyBase::GetCollisionRadius(void)
{
    return collisionRadius_;
}
