
#include"Model.h"
#include"WorldTransform.h"
#include"viewProjection.h"


class Skydome {
public:
	void Initialize(Model* model,ViewProjection* viewProjection);


	void Update();


	void Draw();

private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_=nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_=0u;
	//ビュープロジェクション
	ViewProjection* viewProjection_;
};