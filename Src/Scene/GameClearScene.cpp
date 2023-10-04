#include <DxLib.h>
#include "../Utility/Application.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "GameClearScene.h"

GameClearScene::GameClearScene(void)
{
	imgClear_ = -1;
}

GameClearScene::~GameClearScene(void)
{
}

void GameClearScene::Init(void)
{
	imgClear_ = LoadGraph((Application::PATH_IMAGE + "GameClear.png").c_str());
}

void GameClearScene::Update(void)
{
	// ÉVÅ[ÉìëJà⁄
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
	}
}

void GameClearScene::Draw(void)
{
	DrawRotaGraph(
		Application::SCREEN_SIZE_X / 2,
		Application::SCREEN_SIZE_Y / 2 - 100,
		1.0f, 0.0, imgClear_, true);
}

void GameClearScene::Release(void)
{
	DeleteGraph(imgClear_);
}
