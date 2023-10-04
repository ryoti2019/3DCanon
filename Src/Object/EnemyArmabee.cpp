#include "../Manager/SceneManager.h"
#include "EnemyArmabee.h"

EnemyArmabee::EnemyArmabee(int baseModelId) : EnemyBase(baseModelId)
{
}

void EnemyArmabee::SetParam(void)
{

    // �g�p�������e�ʂƓǂݍ��ݎ��Ԃ̍팸�̂���
    // ���f���f�[�^����������������ɑ��݂����Ȃ�
    modelId_ = MV1DuplicateModel(baseModelId_);

    // �傫���̐ݒ�
    scl_ = { 0.3f, 0.3f, 0.3f };

    // �p�x�̐ݒ�
    rot_ = { 0.0f, -90.0f * DX_PI_F / 180.0f, 0.0f };

    // �ʒu�̐ݒ�
    pos_ = { -350.0f, 30.0f, 75.0f };

    // �E�����Ɉړ�����
    dir_ = { 1.0f, 0.0f, 0.0f };

    // �ړ��X�s�[�h
    speed_ = 0.5f;

    // �����͐������
    isAlive_ = true;

    // �A�j���[�V�������A�^�b�`����
    animAttachNo_ = MV1AttachAnim(modelId_, 2);

    // �A�^�b�`���Ă���A�j���[�V�����̑��Đ����Ԃ��擾����
    animTotalTime_ = MV1GetAttachAnimTotalTime(modelId_, animAttachNo_);

    // �Đ����̃A�j���[�V��������
    stepAnim_ = 0.0f;

    // �A�j���[�V�������x
    speedAnim_ = 30.0f;

    // HP�̐ݒ�
    hp_ = hpMax_ = 2;

    // �Փ˔���p�̋��̔��a
    collisionRadius_ = 35.0f;

    // �Փ˔���p�̋��̒��S�̒������W
    collisionLocalPos_ = { 0.0f, 50.0f, 0.0f };

    // �ړ��p�̃t���O
    up_ = false;
    down_ = false;

    count_ = 0;

}

void EnemyArmabee::Update(void)
{

    //���������Ă����Ȃ���΁A�������Ȃ�
    if (!isAlive_)
    {
        return;
    }

    //�ړ�����
    // �ړ��ʂ̌v�Z(�����~�X�s�[�h)
    VECTOR movePow;
    movePow = VScale(dir_, speed_);
    pos_ = VAdd(pos_, movePow);

    if (count_ == 0)
    {
        up_ = true;
    }

    // ��Ɉړ�
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

    // ���Ɉړ�
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

    // �ړ�������̍d������
    count_++;

    // �A�j���[�V�����Đ�
    // �o�ߎ��Ԃ̎擾
    float deltaTime = 1.0f / SceneManager::DEFAULT_FPS;

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


