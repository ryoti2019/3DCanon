#pragma once
#include "ShotBase.h"
class ShotNormal : public ShotBase
{

public:

	// �R���X�g���N�^
	ShotNormal(int baseModelId, int* blastImgs, int blastAnimNum);

	// �e�̐���(�\���J�n���W�A�e�̐i�s����)
	void CreateShot(VECTOR pos, VECTOR dir) override;

};

