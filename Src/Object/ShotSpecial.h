#pragma once
#include "ShotBase.h"

class ShotSpecial : public ShotBase
{

public:
	// �R���X�g���N�^
	ShotSpecial(int baseModelId, int* blastImgs, int blastAnimNum);

	// �e�̐���(�\���J�n���W�A�e�̐i�s����)
	void CreateShot(VECTOR pos, VECTOR dir);
};

