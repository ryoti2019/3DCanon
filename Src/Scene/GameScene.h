#pragma once
#include <vector>
#include <DxLib.h>
#include "SceneBase.h"
class Stage;
class Cannon;
class ShotBase;
class EnemyBase;
class Camera;

class GameScene : public SceneBase
{

public:

	// �Q�[���I�[�o�[�n�_�Փ˔���p���̔��a
	static constexpr float OVER_COL_RADIUS = 50.0f;

	// �G�̃G���J�E���g�l
	static constexpr int ENCOUNT = 300;

	// ����ł̂ɕK�v�ȓG�̐�
	static constexpr int DEATH_ENEMY_MAX = 3;

	// �R���X�g���N�^
	GameScene(void);

	// �f�X�g���N�^
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	// �X�y�V�����V���b�g�̏�Ԃ̎擾
	bool GetSpecialShot(void);

	// �G�����񂾉�
	void DeathEnemy(void);

	// �J�����̃V�F�C�N���Ԃ̐ݒ�
	void CameraShake(int cnt);

private:

	// �X�e�[�W
	Stage* stage_;

	// �C��
	Cannon* cannon_;

	// �e
	ShotBase* shotBase_;

	// �G�̃��f��
	int enemyModelId_[2];

	int enemy_;

	// �G���
	std::vector<EnemyBase*> enemys_;

	// �G�̔����p�x
	int enCounter_;

	// �Q�[���I�[�o�[�n�_
	VECTOR gameoverPoint_;

	// �Q�[���I�[�o�[����
	bool isGameover_;

	// �Q�[���I�[�o�[�摜
	int imgGameover_;

	// �Q�[���N���A����
	bool isGameclear_;

	// �Q�[���N���A�摜
	int imgGameclear_;

	// �X�y�V�����V���b�g�̔���
	bool specialShot_;

	// �G��|������
	int deathEnemyCounter_;

	// �J�����V�F�C�N�̃J�E���^
	int cnt_;

	// �ꎞ�I�ȕ`��̈�
	int tmpScreen_;

};

