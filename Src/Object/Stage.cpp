#include <DxLib.h>
#include "../Utility/Application.h"
#include "Stage.h"

Stage::Stage(void)
{
}

Stage::~Stage(void)
{
}

void Stage::Init(void)
{

	// 外部ファイルの３Ｄモデルをロード
	modelId_ = MV1LoadModel(
		(Application::PATH_MODEL + "Stage/Stage.mv1").c_str());

	// 背景画像読み込み
	imgBack_ = LoadGraph((Application::PATH_IMAGE + "Sky.jpg").c_str());

	// ３Ｄモデルの大きさを設定(引数は、x, y, zの倍率)
	MV1SetScale(modelId_, { 1.0f, 1.0f, 1.0f });

	// ３Ｄモデルの位置(引数は、３Ｄ座標)
	MV1SetPosition(modelId_, { 0.0f, 0.0f, 0.0f });

	// ３Ｄモデルの向き(引数は、x, y, zの回転量。単位はラジアン。)
	MV1SetRotationXYZ(modelId_, { 0.0f, DX_PI_F, 0.0f });

	// 衝突判定情報(コライダ)の作成
	MV1SetupCollInfo(modelId_);

}

void Stage::Update(void)
{
}

void Stage::Draw(void)
{
	// 背景
	DrawGraph(0, 0, imgBack_, true);

	// ロードされた３Ｄモデルを画面に描画
	MV1DrawModel(modelId_);

}

void Stage::Release(void)
{

	// ロードされた３Ｄモデルをメモリから解放
	MV1DeleteModel(modelId_);

	// 画像の解放
	DeleteGraph(imgBack_);

}

int Stage::GetModelId(void)
{
	return modelId_;
}
