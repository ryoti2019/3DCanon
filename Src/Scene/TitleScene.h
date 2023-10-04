#pragma once
#include "SceneBase.h"
class SceneManager;
class Grid;

class TitleScene : public SceneBase
{

public:

	// �R���X�g���N�^
	TitleScene(void);

	// �f�X�g���N�^
	~TitleScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	// �O���b�h
	Grid* grid_;

	// �摜
	int imgTitle_;

};