#include "../Manager/InputManager.h"
#include "../Object/EnemyBase.h"
#include "Camera.h"

Camera::Camera(void)
{
}

Camera::~Camera()
{
}

void Camera::Init(void)
{

	// �J�����̈ʒu
	pos_ = { 3.0f, 275.0f, -450.0f };

	// �J�����̊p�x
	angles_ = { 25.0f * DX_PI_F / 180.0f, 0.0f, 0.0f };

	// ��_�J������������Ԃɂ���
	ChangeMode(MODE::FREE);

}

void Camera::Update(void)
{
}

void Camera::SetBeforeDraw(void)
{

	// �N���b�v������ݒ肷��(SetDrawScreen�Ń��Z�b�g�����)
	SetCameraNearFar(10.0f, 30000.0f);
	// �J�����̐ݒ�(�ʒu�Ɗp�x�ɂ�鐧��)
	SetCameraPositionAndAngle(
		pos_,
		angles_.x,
		angles_.y,
		angles_.z
	);

	// �N���b�v������ݒ肷��(SetDrawScreen�Ń��Z�b�g�����)
	SetCameraNearFar(10.0f, 30000.0f);
	switch (mode_)
	{
	case Camera::MODE::NONE:
		SetBeforeDraw();
		break;
	case Camera::MODE::FIXED_POINT:
		SetBeforeDrawFixedPoint();
		break;
	case Camera::MODE::FREE:
		SetBeforeDrawFree();
		break;
	}

	// �J�����̐ݒ�(�ʒu�Ɗp�x�ɂ�鐧��)
	SetCameraPositionAndAngle(
		pos_,
		angles_.x,
		angles_.y,
		angles_.z
	);

}

void Camera::SetBeforeDrawFixedPoint(void)
{
}

void Camera::SetBeforeDrawFree(void)
{

	auto& ins = InputManager::GetInstance();

	// WASD�ŃJ�����̈ʒu��ς���
	float movePow = 3.0f;
	if (ins.IsNew(KEY_INPUT_W)) { pos_.z += movePow; };
	if (ins.IsNew(KEY_INPUT_A)) { pos_.x -= movePow; };
	if (ins.IsNew(KEY_INPUT_S)) { pos_.z -= movePow; };
	if (ins.IsNew(KEY_INPUT_D)) { pos_.x += movePow; };
	if (ins.IsNew(KEY_INPUT_Q)) { pos_.y += movePow; };
	if (ins.IsNew(KEY_INPUT_E)) { pos_.y -= movePow; };

	// ���L�[�ŃJ�����̊p�x��ς���
	float rotPow = 1.0f * DX_PI_F / 180.0f;
	//if (ins.IsNew(KEY_INPUT_DOWN)) { angles_.x += rotPow; };
	//if (ins.IsNew(KEY_INPUT_UP)) { angles_.x -= rotPow; };
	//if (ins.IsNew(KEY_INPUT_RIGHT)) { angles_.y += rotPow; };
	//if (ins.IsNew(KEY_INPUT_LEFT)) { angles_.y -= rotPow; };

}

void Camera::ChangeMode(MODE mode)
{
	
	// �J�������[�h�̕ύX
	mode_ = mode;
	// �ύX���̏���������
	switch (mode_)
	{
	case Camera::MODE::FIXED_POINT:
		break;
	case Camera::MODE::FREE:
		break;
	}

}

void Camera::Draw(void)
{

	DrawFormatString(0, 0, 0x000000,
		"�J�������W�F(% .2f, % .2f, % .2f)", pos_.x, pos_.y, pos_.z);

	DrawFormatString(0, 20, 0x000000, "�J�����p�x�F(%.2f, %.2f, %.2f)",
		angles_.x * 180.0f / DX_PI_F,
		angles_.y * 180.0f / DX_PI_F,
		angles_.z * 180.0f / DX_PI_F);

}

void Camera::Release(void)
{
}

void Camera::SetPos(VECTOR pos)
{
	pos_ = pos;
}

void Camera::AddPos(VECTOR pos)
{
	pos_ = { pos_.x + pos.x,
	pos_.y + pos.y,
	pos_.z + pos.z };
}
