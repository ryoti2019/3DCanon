#include "EnemyBirb.h"

EnemyBirb::EnemyBirb(int baseModelId) : EnemyBase(baseModelId)
{
}

void EnemyBirb::SetParam(void)
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
    speed_ = 1.5f;

    // �����͐������
    isAlive_ = true;

    // �A�j���[�V�������A�^�b�`����
    animAttachNo_ = MV1AttachAnim(modelId_, 10);

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

}
