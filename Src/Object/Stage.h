#pragma once
class Stage
{

public:

	// �R���X�g���N�^
	Stage(void);
	// �f�X�g���N�^
	~Stage(void);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	// ���f��ID�̃Q�b�^�[
	int GetModelId(void);

private:

	// 3D���f���̃n���h��ID
	int modelId_;

	// 2D���f����ID
	int imgBack_;

};

