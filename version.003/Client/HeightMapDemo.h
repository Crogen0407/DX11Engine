#pragma once
#include "IExecute.h"
#include "Geometry.h"
class HeightMapDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

private:
	// Object
	shared_ptr<Shader> _shader;
	shared_ptr<Geometry<VertexTextureData>> _geometry;
	shared_ptr<VertexBuffer> _vertexbuffer;
	shared_ptr<IndexBuffer> _indexBuffer;

	Matrix _world = Matrix::Identity;
	Matrix _view = Matrix::Identity;
	Matrix _projection = Matrix::Identity;

	// Camera
	shared_ptr<GameObject> _camera;

	shared_ptr<Texture> _heightMap;
	shared_ptr<Texture> _texture;
};