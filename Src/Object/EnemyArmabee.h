#pragma once
#include "EnemyBase.h"
class EnemyArmabee : public EnemyBase
{
public:

	// �R���X�g���N�^
	EnemyArmabee(int baseModelId);

	// �p�����[�^�ݒ�
	void SetParam(void) override;

	// �X�V����
	void Update(void) override;

private:

	// �ړ��p�̃t���O
	bool up_;
	bool down_;

	// �ړ�������̍d������
	int count_;

};

