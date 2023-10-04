#pragma once
#include <DxLib.h>

class ShotBase
{

public:

	// �Փ˔���p�̋��̔��a
	static constexpr float COL_RADIUS = 10.0f;

	// �e�̏��
	enum class STATE
	{
		NONE,
		SHOT,
		BLAST,
		END
	};

	// �G�̎��
	enum class TYPE
	{
		Normal,
		Special,
		MAX
	};

	// �R���X�g���N�^(���ƂȂ郂�f���̃n���h��ID)
	ShotBase(int baseModelId, int* blastImgs, int blastAnimNum);

	// �f�X�g���N�^
	virtual ~ShotBase(void);

	// �e�̐���(�\���J�n���W�A�e�̐i�s����)
	virtual void CreateShot(VECTOR pos, VECTOR dir);

	// �X�V�X�e�b�v
	void Update(void);
	void UpdateShot(void);
	void UpdateBlast(void);
	void UpdateEnd(void);

	// �`��
	void Draw();
	void DrawShot();
	void DrawBlast();
	void DrawEnd();

	// �������
	void Release(void);

	// �e����
	bool IsShot(void);

	// ���W�̎擾
	VECTOR GetPos(void);

	// ����
	void Blast(void);

	// �Փ˗p�̋��̔��a�̎擾
	float GetCollisionRadius(void);

	// �e�̎�ނ̎擾
	TYPE GetShotType(void);

protected:

	// �e�̏��
	STATE state_;

	// ���ƂȂ�e�̃��f��ID
	int baseModelId_;

	// �e�̃��f��ID
	int modelId_;

	// ����
	VECTOR dir_;

	// �e�̑傫��
	VECTOR scl_;

	// �e�̊p�x
	VECTOR rot_;

	// �e�̍��W
	VECTOR pos_;

	// �e�̈ړ����x
	float speed_;

	// �d��
	float gravityPow_;

	// �����A�j���[�V�����摜�z��̃|�C���^
	int* blastImgs_;

	// �����A�j���[�V������
	int blastAnimNum_;

	// �����̃A�j���[�V�����p�J�E���^
	int blastCntAnim_;

	// �����̃A�j���[�V�������x
	float blastSpeedAnim_;

	// �����̃A�j���[�V�����ԍ�
	int blastIdxAnim_;

	// �Փ˔���p�̋��̔��a
	float collisionRadius_;

	// ��ԑJ��
	void ChangeState(STATE state);

	// �e�̎��
	TYPE shotType_;

};

