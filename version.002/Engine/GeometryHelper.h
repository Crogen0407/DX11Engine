#pragma once
#include "Geometry.h"

class GeometryHelper
{
public:
	static void CreateQuad(shared_ptr<Geometry<VertexColorData>> geometry, Color color);

	static void CreateQuad(shared_ptr<Geometry<VertexTextureData>> geometry);
	static void CreateCube(shared_ptr<Geometry<VertexTextureData>> geometry);
	static void CreateSphere(shared_ptr<Geometry<VertexTextureData>> geometry);
	static void CreateGrid(shared_ptr<Geometry<VertexTextureData>> geometry, UINT sizeX, UINT sizeZ);

	static void CreateQuad(shared_ptr<Geometry<VertexTextureNormalData>> geometry);
	static void CreateCube(shared_ptr<Geometry<VertexTextureNormalData>> geometry);
	static void CreateSphere(shared_ptr<Geometry<VertexTextureNormalData>> geometry);
	static void CreateGrid(shared_ptr<Geometry<VertexTextureNormalData>> geometry, UINT sizeX, UINT sizeZ);

	static void CreateQuad(shared_ptr<Geometry<VertexTextureNormalTangentData>> geometry);
	static void CreateCube(shared_ptr<Geometry<VertexTextureNormalTangentData>> geometry);
	static void CreateSphere(shared_ptr<Geometry<VertexTextureNormalTangentData>> geometry);
	static void CreateGrid(shared_ptr<Geometry<VertexTextureNormalTangentData>> geometry, UINT sizeX, UINT sizeZ);
};

