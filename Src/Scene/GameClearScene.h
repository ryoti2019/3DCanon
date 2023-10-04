#pragma once
#include "SceneBase.h"
class SceneManager;

class GameClearScene : public SceneBase
{

public:

	// �R���X�g���N�^
	GameClearScene(void);

	// �f�X�g���N�^
	~GameClearScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	// �摜
	int imgClear_;

};

