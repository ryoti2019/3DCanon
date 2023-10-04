#pragma once
#include <vector>
#include <DxLib.h>
class EnemyBase;

class Camera
{

public:

	// �J�������[�h
	enum class MODE
	{
		NONE,
		FIXED_POINT, // ��_�J����
		FREE, // �t���[���[�h
	};

	// �R���X�g���N�^
	Camera(void);

	// �f�X�g���N�^
	~Camera();

	// ��������(��{�I�ɍŏ��̂P�񂾂�����)
	void Init(void);

	// �X�V����(���t���[�����s)
	void Update(void);

	// �J�����ݒ�(���t���[�����s)
	void SetBeforeDraw(void);
	void SetBeforeDrawFixedPoint(void);
	void SetBeforeDrawFree(void);

	// �`�揈��(���t���[�����s)
	void Draw(void);

	// �������(��{�I�ɍŌ�̂P�񂾂�����)
	void Release(void);

	// �J�����̍��W�̐ݒ�
	void SetPos(VECTOR pos);

	void AddPos(VECTOR pos);

	// �J�������[�h�̕ύX
	void ChangeMode(MODE mode);

private:

	// �G���
	std::vector<EnemyBase*> enemys_;

	// �J�����̈ʒu
	VECTOR pos_;

	// �J�����̊p�x
	VECTOR angles_;

	// �J�������[�h
	MODE mode_;

	// �J�E���^
	int Cnt_;

};

