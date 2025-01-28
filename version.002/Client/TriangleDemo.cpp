#include "pch.h"
#include "TriangleDemo.h"

void TriangleDemo::Init()
{
	_shader = make_shared<Shader>(L"Triangle.fx");
	{
		_vertices.resize(3);
		_vertices[0].position = { -0.5f, 0.0f, 0.0f };
		_vertices[1].position = {  0.0f, 0.5f, 0.f };
		_vertices[2].position = {  0.5f, 0.0f, 0.f };
	}

	_buffer = make_shared<VertexBuffer>();
	_buffer->Create(_vertices);
}

void TriangleDemo::Update()
{
}

void TriangleDemo::Render()
{
	UINT stride = _buffer->GetStride();
	UINT offset = _buffer->GetOffset();

	DEVICECONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DEVICECONTEXT->IASetVertexBuffers(0, 1, _buffer->GetComPtr().GetAddressOf(), &stride, &offset);

	_shader->Draw(0, 0, 3);
}
