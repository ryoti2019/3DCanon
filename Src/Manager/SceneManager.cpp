#include <chrono>
#include <DxLib.h>
#include "../Common/Fader.h"
#include "../Object/Camera.h"
#include "../Scene/TitleScene.h"
#include "../Scene/GameScene.h"
#include "../Scene/GameClearScene.h"
#include "../Manager/SceneManager.h"

SceneManager* SceneManager::instance_ = nullptr;

void SceneManager::CreateInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new SceneManager();
	}
	instance_->Init();
}

SceneManager& SceneManager::GetInstance(void)
{
	return *instance_;
}

void SceneManager::Init(void)
{

	sceneId_ = SCENE_ID::TITLE;
	waitSceneId_ = SCENE_ID::NONE;

	// �Ó]�E���]�̏�����
	fader_ = new Fader();
	fader_->Init();

	// �J�����̏�����
	camera_ = new Camera();
	camera_->Init();

	isSceneChanging_ = false;

	// �f���^�^�C��
	preTime_ = std::chrono::system_clock::now();

	Init3D();

	// �����V�[���̐ݒ�
	DoChangeScene(SCENE_ID::TITLE);

}

void SceneManager::Init3D(void)
{

	// �w�i�F�ݒ�
	SetBackgroundColor(0, 139, 139);

	// Z�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(true);

	// Z�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(true);

	// �o�b�N�J�����O��L���ɂ���
	SetUseBackCulling(true);

	// ���C�g��L���ɂ���
	SetUseLighting(true);

	// �f�B���N�V���i�����C�g�����̐ݒ�(���K������Ă��Ȃ��Ă��ǂ�)
	// ���ʂ���΂߉��Ɍ����������C�g
	//ChangeLightTypeDir({ 0.00f, -1.00f, 1.00f });

	/*ChangeLightTypePoint({ 0.0f, 40.0f, 180.0f },
		600.0f, 0.000f, 0.001f, 0.000f);*/

	//// �ǉ��|�C���g���C�g�P
	//pointLight1Pos_ = { -390.0f, 100.0f, 50.0f };
	//pointLight1_ = CreatePointLightHandle(
	//	pointLight1Pos_, 100.0f, 0.000f, 0.002f, 0.000f);

	// // �ǉ��|�C���g���C�g�Q
	//pointLight2Pos_ = { 390.0f, 100.0f, 50.0f };
	//pointLight2_ = CreatePointLightHandle(
	//	pointLight2Pos_, 100.0f, 0.000f, 0.002f, 0.000f);

	//// �X�|�b�g���C�g
	//ChangeLightTypeSpot(
	//	{ 20.0f, 260.0f, -210.0f },
	//	{ 0.0f, 0.0f, 1.0f },
	//	6.28f, 0.0f,
	//	200.0f, 0.000f, 0.001f, 0.000f);

	// �f�B�t���[�Y�J���[
	//SetLightDifColor(GetColorF(0.8f, 0.3f, 0.1f, 1.0f));

	// �t�H�O�ݒ�
	SetFogEnable(true);

	// �t�H�O�̐F
	SetFogColor(100, 100, 100);

	// �t�H�O�𔭐������鉜�s���̍ŏ��A�ő勗��
	SetFogStartEnd(500.0f, 1500.0f);

}

void SceneManager::Update(void)
{

	if (scene_ == nullptr)
	{
		return;
	}

	// �f���^�^�C��
	auto nowTime = std::chrono::system_clock::now();
	deltaTime_ = static_cast<float>(
		std::chrono::duration_cast<std::chrono::nanoseconds>(nowTime - preTime_).count() / 1000000000.0);
	preTime_ = nowTime;

	// �Ó]�E���]�̍X�V
	fader_->Update();
	if (isSceneChanging_)
	{
		Fade();
	}
	else
	{
		scene_->Update();
	}

	// �J�����̍X�V
	camera_->Update();
}

void SceneManager::Draw(void)
{
	
	// �`���O���t�B�b�N�̈�̎w��
	// (�R�c�`��Ŏg�p����J�����̐ݒ�Ȃǂ����Z�b�g�����)
	SetDrawScreen(DX_SCREEN_BACK);

	// ��ʂ�������
	ClearDrawScreen();

	// �J�����̐ݒ�
	camera_->SetBeforeDraw();

	// �`��̕`��
	scene_->Draw();

	// �J�����̕`��(�f�o�b�O�p)
	camera_->Draw();

	// �Ó]�E���]�̕`��
	fader_->Draw();

}

void SceneManager::Release(void)
{

	scene_->Release();
	delete scene_;

	// �J�����̊J��
	camera_->Release();
	delete camera_;

	delete fader_;

	//// ������ɕK�����C�g�n���h�������������������邱��
	//DeleteLightHandle(pointLight1_);

}

void SceneManager::ChangeScene(SCENE_ID nextId)
{

	// �t�F�[�h�������I����Ă���V�[����ς���ꍇ�����邽�߁A
	// �J�ڐ�V�[���������o�ϐ��ɕێ�
	waitSceneId_ = nextId;

	// �t�F�[�h�A�E�g(�Ó])���J�n����
	fader_->SetFade(Fader::STATE::FADE_OUT);
	isSceneChanging_ = true;

}

SceneManager::SCENE_ID SceneManager::GetSceneID(void)
{
	return sceneId_;
}

float SceneManager::GetDeltaTime(void) const
{
	//return 1.0f / 60.0f;
	return deltaTime_;
}

Camera* SceneManager::Getcamera(void)
{
	return camera_;
}

SceneManager::SceneManager(void)
{

	sceneId_ = SCENE_ID::NONE;
	waitSceneId_ = SCENE_ID::NONE;

	scene_ = nullptr;
	fader_ = nullptr;

	isSceneChanging_ = false;

	// �f���^�^�C��
	deltaTime_ = 1.0f / 60.0f;

}

SceneManager::~SceneManager(void)
{
	delete instance_;
}

void SceneManager::ResetDeltaTime(void)
{
	deltaTime_ = 0.016f;
	preTime_ = std::chrono::system_clock::now();
}

void SceneManager::DoChangeScene(SCENE_ID sceneId)
{

	// �V�[����ύX����
	sceneId_ = sceneId;

	// ���݂̃V�[�������
	if (scene_ != nullptr)
	{
		scene_->Release();
		delete scene_;
	}

	switch (sceneId_)
	{
	case SCENE_ID::TITLE:
		scene_ = new TitleScene();
		break;
	case SCENE_ID::GAME:
		scene_ = new GameScene();
		break;
	case SCENE_ID::CLEAR:
		scene_ = new GameClearScene();
		break;
	}

	scene_->Init();

	ResetDeltaTime();

	waitSceneId_ = SCENE_ID::NONE;

}

void SceneManager::Fade(void)
{

	Fader::STATE fState = fader_->GetState();
	switch (fState)
	{
	case Fader::STATE::FADE_IN:
		// ���]��
		if (fader_->IsEnd())
		{
			// ���]���I��������A�t�F�[�h�����I��
			fader_->SetFade(Fader::STATE::NONE);
			isSceneChanging_ = false;
		}
		break;
	case Fader::STATE::FADE_OUT:
		// �Ó]��
		if (fader_->IsEnd())
		{
			// ���S�ɈÓ]���Ă���V�[���J��
			DoChangeScene(waitSceneId_);
			// �Ó]���疾�]��
			fader_->SetFade(Fader::STATE::FADE_IN);
		}
		break;
	}

}


