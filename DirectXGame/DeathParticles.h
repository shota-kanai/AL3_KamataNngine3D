#pragma once

#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <array>
#include <numbers>

class DeathParticles {
public:
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	void Update();

	void Draw();

	bool IsFinished() const { return isFinished_; }

private:
	static inline const uint32_t kNumParticles = 8;
	// 存続時間
	static inline const float kDuration = 2.0f;
	// 移動の速さ
	static inline const float kSpeed = 0.05f;
	// 分割した一個分の角度
	static inline const float kAngleUnit = 2.0f * std::numbers::pi_v<float> / kNumParticles;

	Model* modelParticls_ = nullptr;
	std::array<WorldTransform, kNumParticles> worldTransforms_;
	ViewProjection* viewProjection_ = nullptr;
	//終了フラグ
	bool isFinished_ = false;
	//経過時間
	float counter_ = 0.0f;
	//色変更オブジェクト
	//ObjectColor objectColor_;
	//色の数値
	//Vector4 color_;

	
};