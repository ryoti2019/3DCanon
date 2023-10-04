#pragma once
#include <vector>
#include <DxLib.h>
class EnemyBase;

class Camera
{

public:

	// カメラモード
	enum class MODE
	{
		NONE,
		FIXED_POINT, // 定点カメラ
		FREE, // フリーモード
	};

	// コンストラクタ
	Camera(void);

	// デストラクタ
	~Camera();

	// 初期処理(基本的に最初の１回だけ実装)
	void Init(void);

	// 更新処理(毎フレーム実行)
	void Update(void);

	// カメラ設定(毎フレーム実行)
	void SetBeforeDraw(void);
	void SetBeforeDrawFixedPoint(void);
	void SetBeforeDrawFree(void);

	// 描画処理(毎フレーム実行)
	void Draw(void);

	// 解放処理(基本的に最後の１回だけ実装)
	void Release(void);

	// カメラの座標の設定
	void SetPos(VECTOR pos);

	void AddPos(VECTOR pos);

	// カメラモードの変更
	void ChangeMode(MODE mode);

private:

	// 敵情報
	std::vector<EnemyBase*> enemys_;

	// カメラの位置
	VECTOR pos_;

	// カメラの角度
	VECTOR angles_;

	// カメラモード
	MODE mode_;

	// カウンタ
	int Cnt_;

};

