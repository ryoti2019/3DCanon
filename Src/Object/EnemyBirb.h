#pragma once
#include "EnemyBase.h"

class EnemyBirb : public EnemyBase
{

public:

	// コンストラクタ
	EnemyBirb(int baseModelId);

	// パラメータ設定
	void SetParam(void) override;

};

