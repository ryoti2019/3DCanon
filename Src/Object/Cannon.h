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

	// 砲身のX回転制限(最大)
	static constexpr float MAX_ANGLE_X = 15.0f * DX_PI_F / 180.0f;

	// 砲身のX回転制限(最小)
	static constexpr float MIN_ANGLE_X = -30.0f * DX_PI_F / 180.0f;

	// 弾発射後の硬直時間
	static constexpr float SHOT_DELAY = 1.0f;

	// 爆発のサイズ
	static constexpr int BLAST_SIZE_X = 32;
	static constexpr int BLAST_SIZE_Y = 32;

	// 爆発のアニメーション数
	static constexpr int BLAST_ANIM_NUM = 16;

	// コンストラクタ
	Cannon(void);

	// デストラクタ
	~Cannon(void);

	void Init(GameScene* scene);
	void Update(void);
	void Draw(void);
	void Release(void);

	// 弾の取得
	std::vector<ShotBase*> GetShots(void);

private:

#pragma region 砲台

	// ３Ｄモデルの砲台ハンドルID
	int standModelId_;
	VECTOR standScl_;
	VECTOR standRot_;
	VECTOR standPos_;

#pragma endregion

#pragma region 砲身

	// ３Ｄモデルの砲身ハンドルID
	int barrelModelId_;
	VECTOR barrelScl_;
	VECTOR barrelRot_;
	VECTOR barrelPos_;

#pragma endregion

	// 砲台からの相対座標
	VECTOR barrelLocalPos_;

	// 回転操作
	void ProcessRot(void);

	// ゲームシーンのポインタ
	GameScene* gameScene_;

	// ショット(ポインタ)
	std::vector<ShotBase*> shots_;

	// 敵情報
	std::vector<EnemyBase*> enemys_;

	// 弾のモデルID
	int shotModelId_[2];

	// 弾発射後の硬直時間計算用
	float stepShotDelay_;

	// 爆発の画像(本来は外部リソース用の管理クラスを作るべき。弾モデルも。)
	int blastImgs_[BLAST_ANIM_NUM];

	// 発射操作
	void ProcessShot(void);

	// 有効な弾を取得する
	ShotBase* GetValidShot(void);

	// 弾の種類
	//bool nomalShot_;
	//bool specialShot_;

	// 弾の切り替え
	void Shot(void);

	// 弾の種類
	ShotMode mode_;

};

