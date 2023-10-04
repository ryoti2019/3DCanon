#pragma once
#include <string>
#include <vector>
#include <DxLib.h>
class GameScene;

class EnemyBase
{

public:

	// �G�̎��
	enum class TYPE
	{
		Birb,
		Armabee,
		MAX
	};

	// �R���X�g���N�^
	EnemyBase(int baseModelId);

	// �f�X�g���N�^
	virtual ~EnemyBase(void);

	// ��������(�ŏ��̂P��̂ݎ��s)
	virtual void Init(GameScene* scene);

	// �p�����[�^�ݒ�(�������z�֐�)
	virtual void SetParam(void);

	// �X�V����(���t���[�����s)
	virtual void Update(void);

	// �`�揈��(���t���[�����s)
	virtual void Draw(void);

	// �������(�Ō�̂P��̂ݎ��s)
	virtual void Release(void);

	// ���W�̎擾
	VECTOR GetPos(void);

	// ���W�̐ݒ�
	void SetPos(VECTOR pos);

	// ��������
	bool IsAlive(void);

	// ��������
	void SetAlive(bool alive);

	// �_���[�W��^����
	void Damage(int damage);

	// �Փ˗p�̒��S���W�̎擾
	VECTOR GetCollisionPos(void);

	// �Փ˗p�̋��̔��a�̎擾
	float GetCollisionRadius(void);


protected:

	// �Q�[���V�[���̎擾
	GameScene* gameScene_;

	// �摜�̃t�@�C����
	std::string imgFileName_;

	// ���ƂȂ�e�̃��f��ID
	int baseModelId_;

	// �e�̃��f��ID
	int modelId_;

	// �傫��
	VECTOR scl_;

	// �p�x
	VECTOR rot_;

	// �\�����W
	VECTOR pos_;

	// �ړ����x
	float speed_;

	// �ړ�����
	VECTOR dir_;

	// �̗�
	int hp_;

	// �̗͍ő�l
	int hpMax_;

	// ��������
	bool isAlive_;

	// �A�j���[�V�������A�^�b�`�ԍ�
	int animAttachNo_;

	// �A�j���[�V�����̑��Đ�����
	float animTotalTime_;

	// �Đ����̃A�j���[�V��������
	float stepAnim_;

	// �A�j���[�V�������x
	float speedAnim_;

	// �Փ˔���p�̋��̔��a
	float collisionRadius_;

	// �Փ˔���p�̋��̒��S�̒������W
	VECTOR collisionLocalPos_;

};

