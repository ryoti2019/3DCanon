#include <DxLib.h>
#include "../Utility/Application.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "../Object/ShotBase.h"
#include"../Scene/GameScene.h"
#include "ShotNomal.h"
#include "ShotSpecial.h"
#include "EnemyBase.h"
#include "Cannon.h"

Cannon::Cannon(void)
{
}

Cannon::~Cannon(void)
{
}

void Cannon::Init(GameScene* scene)
{

	gameScene_ = scene;

#pragma region �C��

	// �O���t�@�C���̖C��R�c���f�������[�h
	standModelId_ = MV1LoadModel(
		(Application::PATH_MODEL + "Cannon/Stand.mv1").c_str());

	//�C��̑傫��
	standScl_ = { 0.8f, 0.8f, 0.8f };

	// �C��̊p�x
	standRot_ = { 0.0f, 0.0f, 0.0f };

	// �C��̈ʒu
	standPos_ = { 0.0f, 10.0f, -200.0f };

#pragma endregion

#pragma region �C�g

	// �O���t�@�C���̖C�g�R�c���f�������[�h
	barrelModelId_ = MV1LoadModel(
		(Application::PATH_MODEL + "Cannon/Barrel.mv1").c_str());

	// �C�g�̑傫��
	barrelScl_ = { 0.8f, 0.8f, 0.8f };

	// �C�g�̊p�x
	barrelRot_ = { 0.0f, 0.0f, 0.0f };

	// �C�g�̈ʒu
	barrelPos_ = { 0.0f, 110.0f, -200.0f };

	// �C�䂩��̑��΍��W
	barrelLocalPos_ = { 0.0f, 100.0f, 0.0f };

	//barrelPos_ = standPos_ + barrelLocalPos_;
	barrelPos_ = VAdd(standPos_, barrelLocalPos_);

#pragma endregion

	shotModelId_[0] = MV1LoadModel((Application::PATH_MODEL + "Cannon/Shot.mv1").c_str());
	shotModelId_[1] = MV1LoadModel((Application::PATH_MODEL + "Cannon/Shot.mv1").c_str());

	// �e���˂̍d������
	stepShotDelay_ = 0.0f;

	// �����G�t�F�N�g�ǂݍ���
	LoadDivGraph((Application::PATH_IMAGE + "Blast.png").c_str(),
		BLAST_ANIM_NUM, 4, 4, BLAST_SIZE_X, BLAST_SIZE_Y, blastImgs_, true);

	// 3D���f���ɐ�����𔽉f�����邽��
	Update();

}

void Cannon::Update(void)
{

	// �C��̉�]
	ProcessRot();

	// �e�̔���
	ProcessShot();

	// �e�̎�ނ̑I��
	Shot();

	// �C�g
	MV1SetRotationXYZ(barrelModelId_, barrelRot_);
	MV1SetScale(barrelModelId_, barrelScl_);
	MV1SetPosition(barrelModelId_, barrelPos_);

	// �C��
	MV1SetRotationXYZ(standModelId_, standRot_);
	MV1SetPosition(standModelId_, standPos_);
	MV1SetScale(standModelId_, standScl_);

}

void Cannon::Draw(void)
{
	// ���[�h���ꂽ�R�c���f������ʂɕ`��
	MV1DrawModel(standModelId_);
	MV1DrawModel(barrelModelId_);

	// �e�̔��ˈʒu
	VECTOR pos = barrelPos_;

	// �C�g����̑��΍��W
	VECTOR localPos = { 0.0f, 25.0f, 30.0f };

	// �C�g�̉�]�s��
	MATRIX matRot = MGetIdent();
	matRot = MMult(matRot, MGetRotX(barrelRot_.x));
	matRot = MMult(matRot, MGetRotY(barrelRot_.y));
	matRot = MMult(matRot, MGetRotZ(barrelRot_.z));

	// �����Ɠ����v�̂ŁA���΍��W����]
	VECTOR localPosRot = VTransform(localPos, matRot);

	// ���[�J�����W���烏�[���h���W�֕ϊ�
	pos = VAdd(pos, localPosRot);

	// �e�̔��ˈʒu�ڈ�
	DrawSphere3D(pos, 10.0f, 10, 0x00ff00, 0x00ff00, true);

	// �C��̃��f���`��
	MV1DrawModel(standModelId_);

	// �C�g�̃��f���`��(�ꎞ�I�ɔ������ɂ���)
	MV1SetMaterialDifColor(barrelModelId_, 0, GetColorF(1.0f, 1.0f, 1.0f, 0.25f));
	MV1DrawModel(barrelModelId_);

	if (mode_ == ShotMode::Normal)
	{
		DrawFormatString(0, 600, 0xffffff, "Normal");
	}

	if (mode_ == ShotMode::Special)
	{
		DrawFormatString(0, 600, 0xffffff, "Special");
	}

}

void Cannon::Release(void)
{
	// ���[�h���ꂽ�R�c���f����������������
	MV1DeleteModel(standModelId_);
	MV1DeleteModel(barrelModelId_);
	MV1DeleteModel(shotModelId_[0]);
	MV1DeleteModel(shotModelId_[1]);

	for (auto shot : shots_)
	{
		shot->Release();
		delete shot;
	}

	// �ǂݍ��񂾉摜�̉��
	for (int i = 0; i < BLAST_ANIM_NUM; i++)
	{
		DeleteGraph(blastImgs_[i]);
	}
}

std::vector<ShotBase*> Cannon::GetShots(void)
{
	return shots_;
}

void Cannon::ProcessRot(void)
{

	auto& ins = InputManager::GetInstance();
	float rotPow = 1.0f * DX_PI_F / 180.0f;

	//�@�c��]
	if (ins.IsNew(KEY_INPUT_DOWN)) 
	{
		barrelRot_.x += rotPow;
	}

	if (ins.IsNew(KEY_INPUT_UP))
	{ 
		barrelRot_.x -= rotPow;
	}

	// ����](�C�g��Y����])
	if (ins.IsNew(KEY_INPUT_RIGHT))
	{ 
		standRot_.y += rotPow;
		barrelRot_.y += rotPow; 
	}

	if (ins.IsNew(KEY_INPUT_LEFT)) 
	{ 
		standRot_.y -= rotPow;
		barrelRot_.y -= rotPow;
	};

	// �p�x����
	if (MAX_ANGLE_X < barrelRot_.x) { barrelRot_.x = MAX_ANGLE_X; }
	if (MIN_ANGLE_X > barrelRot_.x) { barrelRot_.x = MIN_ANGLE_X; }


}

void Cannon::ProcessShot(void)
{

	auto& ins = InputManager::GetInstance();
	// �U���L�[�������ƁA�e�𐶐�
	if (ins.IsNew(KEY_INPUT_Z) && stepShotDelay_ <= 0.0f)
	{

		// �L���Ȓe���擾����
		ShotBase* shot = GetValidShot();

		// �P�ʍs��(����]�̏��) �P�ʍs��
		MATRIX matRot = MGetIdent();

		// ���ꂼ��̎��̍s������A�X�ɍs����������Ă���
		matRot = MMult(matRot, MGetRotX(barrelRot_.x));
		matRot = MMult(matRot, MGetRotY(barrelRot_.y));
		matRot = MMult(matRot, MGetRotZ(barrelRot_.z));

		// �e�̔��ˈʒu
		VECTOR pos = barrelPos_;

		// �C�g����̑��΍��W
		VECTOR localPos = { 0.0f, 25.0f, 30.0f };

		// �����Ɠ����v�̂ŁA���΍��W����]
		VECTOR localPosRot = VTransform(localPos, matRot);

		// ���[�J�����W���烏�[���h���W�֕ϊ�
		pos = VAdd(pos, localPosRot);

		// ��]�s����g�p���āA�x�N�g������]������
		VECTOR dir = VTransform({ 0.0f, 0.0f, 1.0f }, matRot);

		// �e�𐶐�(�����͉��Ő��ʕ���)
		shot->CreateShot(pos, dir);

		// �e���ˌ�̍d�����ԃZ�b�g
		stepShotDelay_ = SHOT_DELAY;

	}

	// �e���ˌ�̍d�����Ԃ����炵�Ă���
	if (stepShotDelay_ > 0.0f)
	{
		stepShotDelay_ -= 1.0f / SceneManager::DEFAULT_FPS;
	}

}

ShotBase* Cannon::GetValidShot(void)
{

	size_t size = shots_.size();
	for (int i = 0; i < size; i++)
	{
		// �ォ��C�����邩��
		if (!shots_[i]->IsShot() && static_cast<int>(shots_[i]->GetShotType()) == static_cast<int>(mode_))
		{
			return shots_[i];
		}
	}

	// �e�̐���
	ShotBase* shot = nullptr;
	switch (mode_)
	{
	case ShotMode::Normal:
		shot = new ShotNormal(shotModelId_[0], blastImgs_, BLAST_ANIM_NUM);
		break;
	case ShotMode::Special:
		shot = new ShotSpecial(shotModelId_[1], blastImgs_, BLAST_ANIM_NUM);
		break;
	}

	shots_.push_back(shot);

	return shot;

}

void Cannon::Shot(void)
{

	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_X) && gameScene_->GetSpecialShot())
	{
		if (mode_ == ShotMode::Normal)
		{
			mode_ = ShotMode::Special;
			return;
		}

		if (mode_ == ShotMode::Special)
		{
			mode_ = ShotMode::Normal;
			return;
		}

	}



}
