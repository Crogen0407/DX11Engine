#pragma once

struct CameraData
{
	Matrix view = Matrix::Identity;
	Matrix projection = Matrix::Identity;
};

struct TransformData
{
	Matrix world = Matrix::Identity;
};

struct AnimationData
{
	Vec2 spriteOffset;
	Vec2 spriteSize;
	Vec2 textureSize;
	float useAnimation;
	float padding;
};