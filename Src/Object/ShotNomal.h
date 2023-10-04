#pragma once
#include "ShotBase.h"
class ShotNormal : public ShotBase
{

public:

	// コンストラクタ
	ShotNormal(int baseModelId, int* blastImgs, int blastAnimNum);

	// 弾の生成(表示開始座標、弾の進行方向)
	void CreateShot(VECTOR pos, VECTOR dir) override;

};

