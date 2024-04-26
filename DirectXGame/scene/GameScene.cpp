#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	//delete sprite_;
	delete model_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	//textureHandle_=TextureManager::Load("sample.png");
	//sprite_=Sprite::Create(textureHandle_,{100,50});
	textureHandle3D_=TextureManager::Load("sample.png");
	model_=Model::Create();
	//ワールドトランスフォーム
	worldTransform_.Initialize();
	//ビュープロジェクション
	viewProjection_.Initialize();
}

void GameScene::Update() {
	////スプライトの今の座標を取得
	//Vector2 position =sprite_->GetPosition();
	////座標を{2,1}移動
	//position.x+=2.0f;
	//position.y+=1.0f;
	////移動した座標をスプライトに反映
	//sprite_->SetPosition(position);


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

	model_->Draw(worldTransform_,viewProjection_,textureHandle3D_);


	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	

	//sprite_->Draw();


	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
