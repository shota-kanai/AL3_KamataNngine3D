#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include"DebugCamera.h"
#include"skydome.h"

#include<vector>
#include"MapChipField.h"
#include"CameraController.h"
#include "Enemy.h"



/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	
	/// <summary>
	/// 表示ブロックの生成
	/// </summary>
	
	void Draw();
	void GenerateBlocks();
	void CheckAllCollision();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	// テクスチャハンドル
	uint32_t textureHandle_=0;
	//3Dモデルの生成
	Model* model_=nullptr;
	Model* modelBlock_ = nullptr;
	Model* modelPlayer_ =nullptr;
	Model* modelEnemy_ = nullptr;
	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection viewProjection_;
	//自キャラ
	Player* player_=nullptr;
	// 縦横ブロック配列
	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;

	// デバッグカメラ有効
	bool isDebugCameraActive_ = false;
	// デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;
	//スカイドーム
	Skydome* skydome_;
	//スカイドームの3Dモデル
	Model* modelSkydome_=nullptr;

	//マップチップフィールド
	MapChipField* mapChipField_=nullptr;

	CameraController*  cameraController=nullptr;
	//敵
	Enemy* enemy_ = nullptr;
	std::list<Enemy*> enemies_;
};
