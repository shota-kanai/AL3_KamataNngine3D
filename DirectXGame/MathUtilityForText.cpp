#include"MathUtilityForText.h"

// 単項演算子オーバーロード
Vector3 operator+(const Vector3& v) { return v; }
Vector3 operator-(const Vector3& v) { return Vector3(-v.x, -v.y, -v.z); }
Vector3& operator+=(Vector3& lhv, const Vector3& rhv) {
	lhv.x += rhv.x;
	lhv.y += rhv.y;
	lhv.z += rhv.z;
	return lhv;
}
Vector3& operator-=(Vector3& lhv, const Vector3& rhv) {
	lhv.x -= rhv.x;
	lhv.y -= rhv.y;
	lhv.z -= rhv.z;
	return lhv;
}
Vector3& operator*=(Vector3& v, float s) {
	v.x *= s;
	v.y *= s;
	v.z *= s;
	return v;
}
Vector3& operator/=(Vector3& v, float s) {
	v.x /= s;
	v.y /= s;
	v.z /= s;
	return v;
}
// 2項演算子オーバーロード
const Vector3 operator+(const Vector3& v1, const Vector3& v2) {
	Vector3 temp(v1);
	return temp += v2;
}
const Vector3 operator-(const Vector3& v1, const Vector3& v2) {
	Vector3 temp(v1);
	return temp -= v2;
}
const Vector3 operator*(const Vector3& v, float s) {
	Vector3 temp(v);
	return temp *= s;
}
const Vector3 operator*(float s, const Vector3& v) { return v * s; }
const Vector3 operator/(const Vector3& v, float s) {
	Vector3 temp(v);
	return temp /= s;
}


//アフィン変換行列の作成
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotation, const Vector3& translate) {
	//エラー対策
	Vector3 dm=scale;

	//回転
	Matrix4x4 RotateMatY = {
		cosf(rotation.y),0,-sinf(rotation.y),0,
		0,1,0,0,
		sinf(rotation.y),0,cosf(rotation.y),0,
		0,0,0,1
	};

	//平行移動行列の作成
	Matrix4x4 TranslateMat = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		translate.x,translate.y,translate.z,1
	};
	//回転*平行移動だけをワールド変換行列に
	Matrix4x4 ansMat=MatrixMuliply(RotateMatY,TranslateMat);

	return ansMat;
}


//行列の掛け算
Matrix4x4 MatrixMuliply(Matrix4x4 & m1, Matrix4x4 & m2){
	//行列の掛け算
	//縦横に掛けて計算する
	Matrix4x4 result{};

	result.m[0][0]=m1.m[0][0]*m2.m[0][0]+m1.m[0][1]*m2.m[1][0]+m1.m[0][2]*m2.m[2][0]+m1.m[0][3]*m2.m[3][0];
	result.m[0][1]=m1.m[0][0]*m2.m[0][1]+m1.m[0][1]*m2.m[1][1]+m1.m[0][2]*m2.m[2][1]+m1.m[0][3]*m2.m[3][1];
	result.m[0][2]=m1.m[0][0]*m2.m[0][2]+m1.m[0][1]*m2.m[1][2]+m1.m[0][2]*m2.m[2][2]+m1.m[0][3]*m2.m[3][2];
	result.m[0][3]=m1.m[0][0]*m2.m[0][3]+m1.m[0][1]*m2.m[1][3]+m1.m[0][2]*m2.m[2][3]+m1.m[0][3]*m2.m[3][3];

	result.m[1][0]=m1.m[1][0]*m2.m[0][0]+m1.m[1][1]*m2.m[1][0]+m1.m[1][2]*m2.m[2][0]+m1.m[1][3]*m2.m[3][0];
	result.m[1][1]=m1.m[1][0]*m2.m[0][1]+m1.m[1][1]*m2.m[1][1]+m1.m[1][2]*m2.m[2][1]+m1.m[1][3]*m2.m[3][1];
	result.m[1][2]=m1.m[1][0]*m2.m[0][2]+m1.m[1][1]*m2.m[1][2]+m1.m[1][2]*m2.m[2][2]+m1.m[1][3]*m2.m[3][2];
	result.m[1][3]=m1.m[1][0]*m2.m[0][3]+m1.m[1][1]*m2.m[1][3]+m1.m[1][2]*m2.m[2][3]+m1.m[1][3]*m2.m[3][3];

	result.m[2][0]=m1.m[2][0]*m2.m[0][0]+m1.m[2][1]*m2.m[1][0]+m1.m[2][2]*m2.m[2][0]+m1.m[2][3]*m2.m[3][0];
	result.m[2][1]=m1.m[2][0]*m2.m[0][1]+m1.m[2][1]*m2.m[1][1]+m1.m[2][2]*m2.m[2][1]+m1.m[2][3]*m2.m[3][1];
	result.m[2][2]=m1.m[2][0]*m2.m[0][2]+m1.m[2][1]*m2.m[1][2]+m1.m[2][2]*m2.m[2][2]+m1.m[2][3]*m2.m[3][2];
	result.m[2][3]=m1.m[2][0]*m2.m[0][3]+m1.m[2][1]*m2.m[1][3]+m1.m[2][2]*m2.m[2][3]+m1.m[2][3]*m2.m[3][3];

	result.m[3][0]=m1.m[3][0]*m2.m[0][0]+m1.m[3][1]*m2.m[1][0]+m1.m[3][2]*m2.m[2][0]+m1.m[3][3]*m2.m[3][0];
	result.m[3][1]=m1.m[3][0]*m2.m[0][1]+m1.m[3][1]*m2.m[1][1]+m1.m[3][2]*m2.m[2][1]+m1.m[3][3]*m2.m[3][1];
	result.m[3][2]=m1.m[3][0]*m2.m[0][2]+m1.m[3][1]*m2.m[1][2]+m1.m[3][2]*m2.m[2][2]+m1.m[3][3]*m2.m[3][2];
	result.m[3][3]=m1.m[3][0]*m2.m[0][3]+m1.m[3][1]*m2.m[1][3]+m1.m[3][2]*m2.m[2][3]+m1.m[3][3]*m2.m[3][3];


return result;
}

float EaseInOut(float x1, float x2, float t)
{
	float easedT=-(std::cosf(std::numbers::pi_v<float>*t)-1.0f)/2.0f;

return Lerp(x1,x2,easedT);
}

float Lerp(float x1, float x2, float t)
{
return (1.0f-t)*x1+t*x2;
}

Vector3 Lerp(const Vector3 & v1, const Vector3 & v2, float t)
{
return Vector3(Lerp(v1.x,v2.x,t),Lerp(v1.y,v2.y,t),Lerp(v1.z,v2.z,t));
}