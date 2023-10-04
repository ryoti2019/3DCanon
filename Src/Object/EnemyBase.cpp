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

    // �Q�[���V�[���̎擾
    gameScene_ = scene;

    // �G�̃p�����[�^�ݒ�
    SetParam();
    Update();

}

void EnemyBase::SetParam(void)
{
}

void EnemyBase::Update(void)
{

    //���������Ă����Ȃ���΁A�������Ȃ�
    if (!isAlive_)
    {
        return;
    }

    //���ړ�����
    // �ړ��ʂ̌v�Z(�����~�X�s�[�h)
    VECTOR movePow;
    movePow = VScale(dir_, speed_);
    pos_ = VAdd(pos_, movePow);

    // �A�j���[�V�����Đ�
    // �o�ߎ��Ԃ̎擾
    float deltaTime = 1.0f / 60.0f;

    // �A�j���[�V�������Ԃ̐i�s
    stepAnim_ += (speedAnim_ * deltaTime);
    if (stepAnim_ > animTotalTime_)
    {
        // ���[�v�Đ�
        stepAnim_ = 0.0f;
    }

    // �Đ�����A�j���[�V�������Ԃ̐ݒ�
    MV1SetAttachAnimTime(modelId_, animAttachNo_, stepAnim_);

    //���傫���A�p�x�A���W�̂R�c����
    // �傫���̐ݒ�
    MV1SetScale(modelId_, scl_);

    // �p�x�̐ݒ�
    MV1SetRotationXYZ(modelId_, rot_);

    // �ʒu�̐ݒ�
    MV1SetPosition(modelId_, pos_);

}

void EnemyBase::Draw(void)
{

    if (!isAlive_)
    {
        return;
    }

    MV1DrawModel(modelId_);

    // �G�̉~�̕`��
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
