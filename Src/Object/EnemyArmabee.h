#pragma once
#include "EnemyBase.h"
class EnemyArmabee : public EnemyBase
{
public:

	// コンストラクタ
	EnemyArmabee(int baseModelId);

	// パラメータ設定
	void SetParam(void) override;

	// 更新処理
	void Update(void) override;

private:

	// 移動用のフラグ
	bool up_;
	bool down_;

	// 移動した後の硬直時間
	int count_;

};

