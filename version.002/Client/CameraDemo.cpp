#include "pch.h"
#include "CameraDemo.h"
#include "GeometryHelper.h"
#include "InputManager.h"

void CameraDemo::Init()
{
	_shader = make_shared<Shader>(L"ConstantBuffer.fx");

	_geometry = make_shared<Geometry<VertexColorData>>();
	GeometryHelper::CreateQuad(_geometry, {1, 1, 0, 1});

	_vertexbuffer = make_shared<VertexBuffer>();
	_vertexbuffer->Create(_geometry->GetVertices());

	_indexBuffer = make_shared<IndexBuffer>();
	_indexBuffer->Create(_geometry->GetIndices());
}

void CameraDemo::Update()
{
	float speed = 10.f;
	if (GET_BUTTON(KEY_TYPE::A))
		_translation.x -= DELTA_TIME * speed;
	if (GET_BUTTON(KEY_TYPE::D))
		_translation.x += DELTA_TIME * speed;
	if (GET_BUTTON(KEY_TYPE::W))
		_translation.y += DELTA_TIME * speed;
	if (GET_BUTTON(KEY_TYPE::S))
		_translation.y -= DELTA_TIME * speed;

	// SRT
	_world = Matrix::CreateTranslation(_translation);
}

void CameraDemo::Render()
{
	_shader->GetMatrix("World")->SetMatrix((float*)&_world);
	_shader->GetMatrix("View")->SetMatrix((float*)&_view);
	_shader->GetMatrix("Projection")->SetMatrix((float*)&_projection);



	UINT stride = _vertexbuffer->GetStride();
	UINT offset = _vertexbuffer->GetOffset();

	DEVICECONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DEVICECONTEXT->IASetVertexBuffers(0, 1, _vertexbuffer->GetComPtr().GetAddressOf(), &stride, &offset);
	DEVICECONTEXT->IASetIndexBuffer(_indexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);
	_shader->DrawIndexed(0, 0, _indexBuffer->GetCount(), 0, 0);
}
