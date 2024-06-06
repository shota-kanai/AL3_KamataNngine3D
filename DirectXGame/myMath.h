#pragma once
#include"Matrix4x4.h"
#include "Vector3.h"
#include "corecrt_math.h"

// 行列の掛け算
Matrix4x4 MatrixMultiply(Matrix4x4& m1, Matrix4x4& m2);

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate);
