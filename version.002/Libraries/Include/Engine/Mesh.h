#pragma once
#include "ResourceBase.h"
#include "Geometry.h"

class Mesh : public ResourceBase
{
    using Super = ResourceBase;

public:
    Mesh();
    virtual ~Mesh();

	void CreateQuad();
	void CreateCube();
	void CreateGrid(int sizeX, int sizeZ);
	void CreateSphere();

	shared_ptr<VertexBuffer> GetVertexBuffer() { return _vertexBuffer; }
	shared_ptr<IndexBuffer> GetIndexBuffer() { return _indexBuffer; }

private:
	void CreateBuffers();

private:
	// Mesh
	shared_ptr<Geometry<VertexTextureNormalTangentData>> _geometry;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;
};

