#pragma once
#include "SceneBase.h"
class SceneManager;

class GameClearScene : public SceneBase
{

public:

	// コンストラクタ
	GameClearScene(void);

	// デストラクタ
	~GameClearScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	// 画像
	int imgClear_;

};

