#pragma once
#include "ShotBase.h"

class ShotSpecial : public ShotBase
{

public:
	// コンストラクタ
	ShotSpecial(int baseModelId, int* blastImgs, int blastAnimNum);

	// 弾の生成(表示開始座標、弾の進行方向)
	void CreateShot(VECTOR pos, VECTOR dir);
};

