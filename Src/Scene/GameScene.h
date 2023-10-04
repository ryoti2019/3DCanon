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

	// ゲームオーバー地点衝突判定用球体半径
	static constexpr float OVER_COL_RADIUS = 50.0f;

	// 敵のエンカウント値
	static constexpr int ENCOUNT = 300;

	// 球を打つのに必要な敵の数
	static constexpr int DEATH_ENEMY_MAX = 3;

	// コンストラクタ
	GameScene(void);

	// デストラクタ
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	// スペシャルショットの状態の取得
	bool GetSpecialShot(void);

	// 敵が死んだ回数
	void DeathEnemy(void);

	// カメラのシェイク時間の設定
	void CameraShake(int cnt);

private:

	// ステージ
	Stage* stage_;

	// 砲台
	Cannon* cannon_;

	// 弾
	ShotBase* shotBase_;

	// 敵のモデル
	int enemyModelId_[2];

	int enemy_;

	// 敵情報
	std::vector<EnemyBase*> enemys_;

	// 敵の発生頻度
	int enCounter_;

	// ゲームオーバー地点
	VECTOR gameoverPoint_;

	// ゲームオーバー判定
	bool isGameover_;

	// ゲームオーバー画像
	int imgGameover_;

	// ゲームクリア判定
	bool isGameclear_;

	// ゲームクリア画像
	int imgGameclear_;

	// スペシャルショットの判定
	bool specialShot_;

	// 敵を倒した数
	int deathEnemyCounter_;

	// カメラシェイクのカウンタ
	int cnt_;

	// 一時的な描画領域
	int tmpScreen_;

};

