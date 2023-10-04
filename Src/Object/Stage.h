#pragma once
class Stage
{

public:

	// コンストラクタ
	Stage(void);
	// デストラクタ
	~Stage(void);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	// モデルIDのゲッター
	int GetModelId(void);

private:

	// 3DモデルのハンドルID
	int modelId_;

	// 2DモデルのID
	int imgBack_;

};

