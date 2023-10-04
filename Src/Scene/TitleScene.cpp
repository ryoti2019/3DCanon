#include <string>
#include <DxLib.h>
#include "../Utility/Application.h"
#include "../Utility/AsoUtility.h"
#include "../Object/Grid.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "TitleScene.h"

TitleScene::TitleScene(void)
{
	imgTitle_ = -1;
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{

	imgTitle_ = LoadGraph((Application::PATH_IMAGE + "Title.png").c_str());
	// îwåiÇÃèâä˙âª
	grid_->Init();

}

void TitleScene::Update(void)
{

	// ÉVÅ[ÉìëJà⁄
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
	}

	// îwåiÇÃçXêV
	grid_->Update();

}

void TitleScene::Draw(void)
{

	// îwåiÇÃï`âÊ
	grid_->Draw();

	DrawRotaGraph(
		Application::SCREEN_SIZE_X / 2,
		Application::SCREEN_SIZE_Y / 2 - 100,
		1.0f, 0.0, imgTitle_, true);

	VECTOR pos = VGet(0.0f, 0.0f, 0.0f);

	// îíÇ¢ãÖëÃ
	DrawSphere3D(pos, 50.0f, 10, 0xffffff, 0xffffff, true);

	pos = VGet(0.0f, 0.0f, 100.0f);
	// ê‘Ç¢ãÖëÃ
	DrawSphere3D(pos, 80.0f, 10, 0xff0000, 0xff0000, true);

}

void TitleScene::Release(void)
{
	DeleteGraph(imgTitle_);
}
