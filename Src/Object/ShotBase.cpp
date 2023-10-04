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
	// �@STATE����

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

	// �e���ړ�������

	// �ړ��ʂ̌v�Z(�����~�X�s�[�h)
	VECTOR movePow;
	//movePow.x = dir_.x * speed_;
	//movePow.y = dir_.y * speed_;
	//movePow.z = dir_.z * speed_;
	movePow = VScale(dir_, speed_);

	// �ړ�����(���W+�ړ���)
	//pos_.x += movePow.x;
	//pos_.y += movePow.y;
	//pos_.z += movePow.z;
	pos_ = VAdd(pos_, movePow);

	//pos_ = VAdd(pos_, VScale(dir_, speed_));

	// �X�ɉ����x�I�ɏd�͂�������
	gravityPow_ += SceneManager::GRAVITY / SceneManager::DEFAULT_FPS;

	// pos_.y -= gravityPow_;

	pos_ = VAdd(pos_, VScale({ 0.0f, -1.0f, 0.0f }, gravityPow_));

	// �傫���̐ݒ�
	MV1SetScale(modelId_, scl_);

	// �p�x�̐ݒ�
	MV1SetRotationXYZ(modelId_, rot_);

	// �ʒu�̐ݒ�
	MV1SetPosition(modelId_, pos_);

}

void ShotBase::UpdateBlast(void)
{
	// �����A�j���[�V����
	blastCntAnim_++;

	// �����̃A�j���[�V�����ԍ�
	blastIdxAnim_ = static_cast<int>(static_cast<float>(blastCntAnim_) * blastSpeedAnim_) % blastAnimNum_;

	// �����A�j���[�V�����̏I������
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
	// �BSTATE����

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
	// 2D�̃A�j���[�V�����`��
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
	//��STATE��SHOT��Ԃ�������true
	return state_ == STATE::SHOT;
}

void ShotBase::ChangeState(STATE state)
{
	// ��Ԃ̍X�V
	state_ = state;

	// ��ԑJ�ڎ��̏�����
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
	//��BLAST��Ԃ֑J�ڂ�����
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
