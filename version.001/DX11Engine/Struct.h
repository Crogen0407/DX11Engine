#pragma once
#include "Types.h"

struct CameraData
{
	Matrix view = Matrix::Identity;
	Matrix projection = Matrix::Identity;
};

struct TransformData
{
	Matrix world = Matrix::Identity;
};