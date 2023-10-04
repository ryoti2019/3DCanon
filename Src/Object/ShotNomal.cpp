#include "ShotNomal.h"

ShotNormal::ShotNormal(int baseModelId, int* blastImgs, int blastAnimNum) : ShotBase(baseModelId,  blastImgs, blastAnimNum)
{
}

void ShotNormal::CreateShot(VECTOR pos, VECTOR dir)
{

	// �e�̎��
	shotType_ = TYPE::Normal;

	// �g�p�������e�ʂƓǂݍ��ݎ��Ԃ̍팸�̂���
	// ���f���f�[�^����������������ɑ��݂����Ȃ�
	modelId_ = MV1DuplicateModel(baseModelId_);

	// �e�̑傫����ݒ�
	scl_ = { 0.8f, 0.8f, 0.8f };

	// �e�̊p�x��ݒ�
	rot_ = { 0.0f, 0.0f, 0.0f };

	// �e�̔��ˈʒu��ݒ�
	pos_ = pos;

	// �e�̔��˕����̐ݒ�
	dir_ = dir;

	// �e�̔��a
	collisionRadius_ = 10.0f;

	// �e�̑��x
	speed_ = 8.0f;

	// �d��
	gravityPow_ = 0.0f;

	// �����̃A�j���[�V�����p�J�E���^
	blastCntAnim_ = 0;

	// �����̃A�j���[�V�������x
	blastSpeedAnim_ = 0.3f;

	// ��Ԃ̏�����
	state_ = STATE::NONE;

	// �Փ˔���p�̋��̔��a
	collisionRadius_ = 10.0f;

	// ��ԑJ��
	ChangeState(STATE::SHOT);

}
