#pragma once
#include <Vector3.h>
#include<Matrix4x4.h>
#include<math.h>
#include<cmath>
#include<numbers>
	// 単項演算子オーバーロード
	Vector3 operator+(const Vector3& v);
	Vector3 operator-(const Vector3& v);
	// 代入演算子オーバーロード
	Vector3& operator+=(Vector3& lhs, const Vector3& rhv);
	Vector3& operator-=(Vector3& lhs, const Vector3& rhv);
	Vector3& operator*=(Vector3& v, float s);
	Vector3& operator/=(Vector3& v, float s);
	// 2項演算子オーバーロード
	const Vector3 operator+(const Vector3& v1, const Vector3& v2);
	const Vector3 operator-(const Vector3& v1, const Vector3& v2);
	const Vector3 operator*(const Vector3& v, float s);
	const Vector3 operator*(float s, const Vector3& v);
	const Vector3 operator/(const Vector3& v, float s);

	
	//行列の掛け算
	Matrix4x4 MatrixMuliply(Matrix4x4& m1,Matrix4x4& m2);
	Matrix4x4 MakeRotateXMatrix(float radian);
	Matrix4x4 MakeRotateYMatrix(float radian);
	Matrix4x4 MakeRotateZMatrix(float radian);
	//アフィン変換行列の作成
	Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotation, const Vector3& translate);
	//EaselnOut関数
	float EaseInOut(float x1,float x2,float t);
	float Lerp(float x1,float x2,float t);
	Vector3 Lerp(const Vector3& v1,const Vector3& v2,float t);
	Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);