#pragma once
#include <DxLib.h>

class ShotBase
{

public:

	// 衝突判定用の球体半径
	static constexpr float COL_RADIUS = 10.0f;

	// 弾の状態
	enum class STATE
	{
		NONE,
		SHOT,
		BLAST,
		END
	};

	// 敵の種類
	enum class TYPE
	{
		Normal,
		Special,
		MAX
	};

	// コンストラクタ(元となるモデルのハンドルID)
	ShotBase(int baseModelId, int* blastImgs, int blastAnimNum);

	// デストラクタ
	virtual ~ShotBase(void);

	// 弾の生成(表示開始座標、弾の進行方向)
	virtual void CreateShot(VECTOR pos, VECTOR dir);

	// 更新ステップ
	void Update(void);
	void UpdateShot(void);
	void UpdateBlast(void);
	void UpdateEnd(void);

	// 描画
	void Draw();
	void DrawShot();
	void DrawBlast();
	void DrawEnd();

	// 解放処理
	void Release(void);

	// 弾判定
	bool IsShot(void);

	// 座標の取得
	VECTOR GetPos(void);

	// 爆発
	void Blast(void);

	// 衝突用の球体半径の取得
	float GetCollisionRadius(void);

	// 弾の種類の取得
	TYPE GetShotType(void);

protected:

	// 弾の状態
	STATE state_;

	// 元となる弾のモデルID
	int baseModelId_;

	// 弾のモデルID
	int modelId_;

	// 方向
	VECTOR dir_;

	// 弾の大きさ
	VECTOR scl_;

	// 弾の角度
	VECTOR rot_;

	// 弾の座標
	VECTOR pos_;

	// 弾の移動速度
	float speed_;

	// 重力
	float gravityPow_;

	// 爆発アニメーション画像配列のポインタ
	int* blastImgs_;

	// 爆発アニメーション数
	int blastAnimNum_;

	// 爆発のアニメーション用カウンタ
	int blastCntAnim_;

	// 爆発のアニメーション速度
	float blastSpeedAnim_;

	// 爆発のアニメーション番号
	int blastIdxAnim_;

	// 衝突判定用の球体半径
	float collisionRadius_;

	// 状態遷移
	void ChangeState(STATE state);

	// 弾の種類
	TYPE shotType_;

};

