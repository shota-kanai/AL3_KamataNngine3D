#include"Enemy.h"
#include "myMath.h"
#include <cassert>
#include <numbers>

void Enemy::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {
	assert(model);

	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> * 3.0f / 2.0f;
	viewProjection_ = viewProjection;

	velocity_ = {-kWalkSpeed, 0, 0};
	walkTimer = 0.0f;
}

void Enemy::Update() {
	//タイマーを加算
	walkTimer += 1.0f / 60.0f;
	// 回転アニメーション
	float param = std::sin((2*3.14f)*walkTimer/kWalkMotionTime);
	float radian = kWalkMotionAngleStart + kWalkMotionAngleEnd * (param + 1.0f) / 2.0f;
	worldTransform_.rotation_.x = (radian) * 3.14f / 360;
	/*worldTransform_.rotation_.x=std::sin(std::numbers::pi_v<float>*2.0f*walkTimer/kWalkMotionTime);*/

	// 移動
	worldTransform_.translation_.x += velocity_.x;
	// 行列計算
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw() {
	// モデル描画
	model_->Draw(worldTransform_, *viewProjection_);
}

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos{};
	// ワールド行列の平行移動成分を取得(ワールド座標)
	/*worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;*/
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

AABB Enemy::GetAABB() {
	Vector3 worldPos = GetWorldPosition();

	AABB aabb{};

	aabb.min = {
	    worldPos.x - kWidth / 2.0f, worldPos.y - kWidth / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {
	    worldPos.x + kHeight / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kHeight / 2.0f};

	return aabb;
}

void Enemy::OnCollision(const Player* player) { (void)player; }