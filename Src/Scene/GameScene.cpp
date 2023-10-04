#include <string>
#include <DxLib.h>
#include "../Utility/Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Object/Camera.h"
#include "../Object/Stage.h"
#include "../Object/Cannon.h"
#include "../Object/ShotBase.h"
#include "../Object/EnemyBase.h"
#include "../Object/EnemyBirb.h"
#include "../Object/EnemyArmabee.h"

#include "GameScene.h"

GameScene::GameScene(void)
{
}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
{

	// �J����
	Camera* camera = SceneManager::GetInstance().Getcamera();
	camera->ChangeMode(Camera::MODE::FIXED_POINT);

	// �X�e�[�W�̏�����
	stage_ = new Stage(); 
	stage_->Init();

	// �C��̏�����
	cannon_ = new Cannon();
	cannon_->Init(this);

	// �J�������t���[���[�h�ɂ���
	SceneManager::GetInstance().Getcamera()->ChangeMode(Camera::MODE::FREE);

	enemyModelId_[0] = MV1LoadModel((Application::PATH_MODEL + "Enemy/Birb.mv1").c_str());

	enemyModelId_[1] = MV1LoadModel((Application::PATH_MODEL + "Enemy/Armabee.mv1").c_str());

	// �Q�[���I�[�o�[�n�_
	gameoverPoint_ = { 450.0f, 30.0f, 75.0f };

	// �Q�[���I�[�o�[����
	isGameover_ = false;

	// �Q�[���I�[�o�[�摜
	imgGameover_ =
		LoadGraph((Application::PATH_IMAGE + "Gameover.png").c_str());

	// �Q�[���N���A����
	isGameclear_ = false;

	// �Q�[���N���A�摜
	imgGameclear_ = LoadGraph((Application::PATH_IMAGE + "GameClear.png").c_str());

	// �G�����񂾐�
	deathEnemyCounter_ = 0;

	// �X�y�V�����V���b�g���łĂ邩
	specialShot_ = false;
	cnt_ = 0;

	// �ꎞ�I�ȕ`��̈�
	tmpScreen_ = MakeScreen(Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, true);
}

void GameScene::Update(void)
{

	//if (isGameover_ || isGameclear_)
	//{
	//	// �Q�[���I�[�o�[�Ȃ珈�����Ȃ�
	//	return;
	//}

	// �Q�[���I�[�o�[����
	for (auto enemy : enemys_)
	{
		if (AsoUtility::IsHitSpheres(
			enemy->GetCollisionPos(), enemy->GetCollisionRadius(),
			gameoverPoint_, 30.0f))
		{
			isGameover_ = true;
		}
	}

	//// �Q�[���N���A����
	//for (auto enemy : enemys_)
	//{
	//	if (!enemy->IsAlive())
	//	{
	//		isGameclear_ = true;
	//	}
	//}

	// �X�e�[�W�̍X�V
	stage_->Update();

	// �C��̍X�V
	cannon_->Update();

	// �G�̍X�V
	for (auto enemy : enemys_)
	{
		enemy->Update();
	}

	// �G�̏�����
	if (enCounter_ > ENCOUNT)
	{
		// �G���J�E���g���Z�b�g
		enCounter_ = 0;

		// �G�̐���
		EnemyBase* enemy = nullptr;
		int eType = GetRand(static_cast<int>(EnemyBase::TYPE::MAX) - 1);
		EnemyBase::TYPE type = static_cast<EnemyBase::TYPE>(eType);
		switch (type)
		{
		case EnemyBase::TYPE::Birb:
			enemy = new EnemyBirb(enemyModelId_[0]);
			break;
		case EnemyBase::TYPE::Armabee:
			enemy = new EnemyArmabee(enemyModelId_[1]);
			break;
		}

		enemy->Init(this);
		enemys_.push_back(enemy);

	}
	enCounter_++;

	// �X�e�[�W���f��ID
	int stageModelId = stage_->GetModelId();

	// �e�̍X�V
	auto shots = cannon_->GetShots();
	for (auto shot : shots)
	{

		shot->Update();

		// �e��SHOT��Ԃ���Ȃ�������Փ˔��肵�Ȃ�
		if (!shot->IsShot())
		{
			// �������⏈���I����́A�ȍ~�̏����͎��s���Ȃ�
			continue;
		}

		// �X�e�[�W���f���Ƃ̏Փ˔���
		auto info = MV1CollCheck_Sphere(
			stageModelId, -1, shot->GetPos(), shot->GetCollisionRadius());

		if (info.HitNum > 0)
		{
			// �Փ˂��Ă���
			shot->Blast();
		}

		// �����蔻�茋�ʃ|���S���z��̌�n��������
		MV1CollResultPolyDimTerminate(info);

		// ���݂��̔��a�̍��v
		//float radius = enemy->GetCollisionRadius() + shot->GetCollisionRadius();
		// ���W�̍����炨�݂��̋��������
		//VECTOR diff = VSub(enemy->GetCollisionPos(), shot->GetPos());
		// �O�����̒藝�Ŕ�r(SqrMagnitude�Ɠ���)
		//float dis = (diff.x * diff.x) + (diff.y * diff.y) + (diff.z * diff.z);
		// ���̂Ƌ��̂̏Փ˔���
		//if (dis < (radius * radius))
		//{
			// �G�Ƀ_���[�W��^����
			//enemy->Damage(1);
			//shot->Blast();
			//break;
		//}

		// �G�Ƃ̏Փ˔���
		for (auto enemy : enemys_)
		{
			if (enemy->IsAlive())
			{
				if (AsoUtility::IsHitSpheres(
					enemy->GetCollisionPos(), enemy->GetCollisionRadius(),
					shot->GetPos(), shot->GetCollisionRadius()))
				{
					// �G�Ƀ_���[�W��^����
					enemy->Damage(1);
					shot->Blast();
					break;
				}
			}
		}
	}

	// �Q�[���I�[�o�[����
	for (auto enemy : enemys_)
	{
		// ���̂Ƌ��̂̏Փ˔���
		if (AsoUtility::IsHitSpheres(
			enemy->GetCollisionPos(), enemy->GetCollisionRadius(),
			gameoverPoint_, OVER_COL_RADIUS))
		{
			isGameover_ = true;
			break;
		}
	}

	//// �V�[���J��
	//InputManager& ins = InputManager::GetInstance();
	//if (ins.IsTrgDown(KEY_INPUT_SPACE))
	//{
	//	SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
	//}

	// �R�̓G��|������X�y�V�����V���b�g���łĂ�
	if (deathEnemyCounter_ >= DEATH_ENEMY_MAX)
	{
		specialShot_ = true;
	}

	// �G��5�̓|������N���A
	if (deathEnemyCounter_ >= 5)
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::CLEAR);
	}

}

void GameScene::Draw(void)
{

	//�U��
	if (cnt_ > 0)
	{
		cnt_--;
		float s[5] = { -5.0f,2.5f,0.0f,-2.5f,5.0f };
		int shake = cnt_ % 5;

		SceneManager::GetInstance().Getcamera()->AddPos({ s[shake], s[shake], 0.0f});
		//DrawGraph(shake, shake, tmpScreen_, true);
		if (cnt_ <= 0)
		{
			SceneManager::GetInstance().Getcamera()->SetPos({ 3.0f, 275.0f, -450.0f });
			cnt_ = 0;
		}
	}

	// �X�e�[�W�̕`��
	stage_->Draw();

	// �C��̕`��
	cannon_->Draw();

	// Y���W�ɏ������Z
	VECTOR point = { 0.0f, 30.0f, 0.0f };

	// �G�̕`��
	for (auto enemy : enemys_)
	{
		enemy->Draw();
		// �Q�[���I�[�o�[�n�_�̉~�̕`��
		//DrawSphere3D(VAdd(gameoverPoint_, enemy->GetCollisionPos()), 10.0f, 10, 0xff0000, 0xff0000, false);
		//DrawSphere3D(VAdd(gameoverPoint_, point), 30.0f, 10, 0xff0000, 0xff0000, false);
	}

	// �e�̍X�V
	auto shots = cannon_->GetShots();
	for (auto shot : shots)
	{
		shot->Draw();

		DrawSphere3D(shot->GetPos(), shot->GetCollisionRadius(),
			10, 0xff0000, 0xff0000, false);

	}

	if (isGameover_)
	{
		// �Q�[���I�[�o�[�摜
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2,
					  Application::SCREEN_SIZE_Y / 2,
					  1.0f, 0.0f, imgGameover_, true);
	}

	if (isGameclear_)
	{
		// �Q�[���N���A�摜
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2,
			Application::SCREEN_SIZE_Y / 2,
			1.0f, 0.0f, imgGameclear_, true);
	}

	// �f�o�b�O�p
	DrawSphere3D(gameoverPoint_, OVER_COL_RADIUS,
		10, 0xff0000, 0xff0000, false);

}

void GameScene::Release(void)
{

	// �X�e�[�W�̊J��
	stage_->Release();

	// �C��̊J��
	cannon_->Release();

	// �G�̊J��
	for (auto enemy : enemys_)
	{
		enemy->Release();
	}

	//// �e�̊J��
	//auto shots = cannon_->GetShots();
	//for (auto shot : shots)
	//{
	//	shot->Release();
	//	//delete shot;
	//}

	// �G�̃��f���̊J��
	MV1DeleteModel(enemyModelId_[0]);
	MV1DeleteModel(enemyModelId_[1]);

	// �Q�[���I�[�o�[�̊J��
	DeleteGraph(imgGameover_);

}

bool GameScene::GetSpecialShot(void)
{
	return specialShot_;
}

void GameScene::DeathEnemy(void)
{
	deathEnemyCounter_++;
}

void GameScene::CameraShake(int cnt)
{
	cnt_ = cnt;
}
