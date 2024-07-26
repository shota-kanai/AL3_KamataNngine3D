#include <cassert>
#include<cstdint>
#include "GameScene.h"
#include "TextureManager.h"


GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete modelPlayer_;
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform*& worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
			worldTransformBlock=nullptr;
		}
	}
	worldTransformBlocks_.clear();

	delete debugCamera_;
	delete modelSkydome_;
	delete mapChipField_;
	delete modelBlock_;
	delete cameraController;

}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//ファイル名を指定してテクスチャを読み込む
	textureHandle_=TextureManager::Load("mario.jpg");
	//3Dモデルの生成
	model_=Model::Create();
	modelBlock_ = Model::CreateFromOBJ("block");
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();


	//スカイドームの初期化
	skydome_=new Skydome();
	skydome_->Initialize(model_,&viewProjection_);
	//3Dモデルの生成
	modelSkydome_=Model::CreateFromOBJ("sphere",true);
	skydome_->Initialize(modelSkydome_,&viewProjection_);

	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280,720);

	//マップチップフィールドの生成と初期化
	mapChipField_=new MapChipField;
	mapChipField_->LoadMapChipCsv("Resources/blocks.csv");

	//自キャラの生成
	player_=new Player();
	// 座標をマップチップ番号で指定
	Vector3 playerPosition=mapChipField_->GetMapChipPositionByIndex(2,18);
	//自キャラの初期化
	modelPlayer_=Model::CreateFromOBJ("player",true);
	player_->Initialize(modelPlayer_,&viewProjection_,playerPosition);

	player_->SetMapChipField(mapChipField_);

	GenerateBlocks();

	//カメラコントローラーの初期化
	cameraController = new CameraController;
	cameraController->Initialize();
	cameraController->SetTarget(player_);
	cameraController->Reset();

	CameraController::Rect cameraArea = {14.0f, 100 - 12.0f, 7.6f, 7.6f};
	cameraController->SetMovableArea(cameraArea);
}
void GameScene::GenerateBlocks() {

	// 要素数
	uint32_t numBlockVirtical = mapChipField_->GetNumBlockVirtical();
	uint32_t numBlockHorizontal = mapChipField_->GetNumBlockHorizontal();
	
	// 要素数を変更する
	worldTransformBlocks_.resize(numBlockVirtical);

	// キューブの生成
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		worldTransformBlocks_[i].resize(numBlockHorizontal);
	}

	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		for (uint32_t j = 0; j < numBlockHorizontal; ++j) {
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock){
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}
}

void GameScene::Update() {
	#ifdef _DEBUG
	if (input_->TriggerKey(DIK_SPACE)) {
		if (isDebugCameraActive_ == true)
			isDebugCameraActive_ = false;
		else
			isDebugCameraActive_ = true;
	}
#endif
	cameraController->Update();
	// カメラ処理
	if (isDebugCameraActive_) {
		// デバッグカメラの更新
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
		viewProjection_.matView=cameraController->GetViewProjection().matView;
		viewProjection_.matProjection=cameraController->GetViewProjection().matProjection;
		// ビュープロジェクション行列の更新と転送
		viewProjection_.TransferMatrix();
	}

	//自キャラの更新
	player_->Update();
	//カメラの更新
	cameraController->Update();
	//スカイドームの更新
	skydome_->Update();
	// 縦横ブロック更新
	for (std::vector<WorldTransform*>& worldTransformBlockTate : worldTransformBlocks_) {
		for (WorldTransform*& worldTransformBlockYoko : worldTransformBlockTate) {
			if (!worldTransformBlockYoko)
				continue;

				// アフィン変換行列の作成
				worldTransformBlockYoko->UpdateMatrix();
		
		}
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
	

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	//自キャラの描画
	player_->Draw();
	//縦横ブロック描画
	for (std::vector<WorldTransform*>& worldTransformBlockTate : worldTransformBlocks_) {
		for (WorldTransform*& worldTransformBlockYoko : worldTransformBlockTate) {
			if (!worldTransformBlockYoko)
				continue;

			modelBlock_->Draw(*worldTransformBlockYoko, viewProjection_);
		}
	}
	//スカイドームの描画
	skydome_->Draw();

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}


