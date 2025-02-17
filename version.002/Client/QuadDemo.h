#pragma once
#include "IExecute.h"
#include "Geometry.h"
class QuadDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

private:
	shared_ptr<Shader> _shader;
	shared_ptr<Geometry<VertexColorData>> _geometry;
	shared_ptr<VertexBuffer> _vertexbuffer;
	shared_ptr<IndexBuffer> _indexBuffer;
};

