#pragma once
#include <vector>
#include <DxLib.h>
class ShotBase;
class EnemyBase;
class GameScene;

class Cannon
{

public:


	enum ShotMode {
		Normal,
		Special,
	};

	// �C�g��X��]����(�ő�)
	static constexpr float MAX_ANGLE_X = 15.0f * DX_PI_F / 180.0f;

	// �C�g��X��]����(�ŏ�)
	static constexpr float MIN_ANGLE_X = -30.0f * DX_PI_F / 180.0f;

	// �e���ˌ�̍d������
	static constexpr float SHOT_DELAY = 1.0f;

	// �����̃T�C�Y
	static constexpr int BLAST_SIZE_X = 32;
	static constexpr int BLAST_SIZE_Y = 32;

	// �����̃A�j���[�V������
	static constexpr int BLAST_ANIM_NUM = 16;

	// �R���X�g���N�^
	Cannon(void);

	// �f�X�g���N�^
	~Cannon(void);

	void Init(GameScene* scene);
	void Update(void);
	void Draw(void);
	void Release(void);

	// �e�̎擾
	std::vector<ShotBase*> GetShots(void);

private:

#pragma region �C��

	// �R�c���f���̖C��n���h��ID
	int standModelId_;
	VECTOR standScl_;
	VECTOR standRot_;
	VECTOR standPos_;

#pragma endregion

#pragma region �C�g

	// �R�c���f���̖C�g�n���h��ID
	int barrelModelId_;
	VECTOR barrelScl_;
	VECTOR barrelRot_;
	VECTOR barrelPos_;

#pragma endregion

	// �C�䂩��̑��΍��W
	VECTOR barrelLocalPos_;

	// ��]����
	void ProcessRot(void);

	// �Q�[���V�[���̃|�C���^
	GameScene* gameScene_;

	// �V���b�g(�|�C���^)
	std::vector<ShotBase*> shots_;

	// �G���
	std::vector<EnemyBase*> enemys_;

	// �e�̃��f��ID
	int shotModelId_[2];

	// �e���ˌ�̍d�����Ԍv�Z�p
	float stepShotDelay_;

	// �����̉摜(�{���͊O�����\�[�X�p�̊Ǘ��N���X�����ׂ��B�e���f�����B)
	int blastImgs_[BLAST_ANIM_NUM];

	// ���ˑ���
	void ProcessShot(void);

	// �L���Ȓe���擾����
	ShotBase* GetValidShot(void);

	// �e�̎��
	//bool nomalShot_;
	//bool specialShot_;

	// �e�̐؂�ւ�
	void Shot(void);

	// �e�̎��
	ShotMode mode_;

};

