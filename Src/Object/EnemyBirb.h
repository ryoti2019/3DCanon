#pragma once
#include "EnemyBase.h"

class EnemyBirb : public EnemyBase
{

public:

	// �R���X�g���N�^
	EnemyBirb(int baseModelId);

	// �p�����[�^�ݒ�
	void SetParam(void) override;

};

