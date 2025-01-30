#include "pch.h"
#include "CameraDemo.h"
#include "GeometryHelper.h"
#include "InputManager.h"
#include "Camera.h"
#include "GameObject.h"
#include "CameraScript.h"

void CameraDemo::Init()
{
	_shader = make_shared<Shader>(L"World.fx");

	_geometry = make_shared<Geometry<VertexColorData>>();
	GeometryHelper::CreateQuad(_geometry, {1, 1, 0, 1});

	_vertexbuffer = make_shared<VertexBuffer>();
	_vertexbuffer->Create(_geometry->GetVertices());

	_indexBuffer = make_shared<IndexBuffer>();
	_indexBuffer->Create(_geometry->GetIndices());

	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform();
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());
	_camera->GetTransform()->SetPosition({ 0, 0, -10 });
}

void CameraDemo::Update()
{
	_camera->Update();
}

void CameraDemo::Render()
{
	_shader->GetMatrix("World")->SetMatrix((float*)&_world);
	_shader->GetMatrix("View")->SetMatrix((float*)&Camera::View);
	_shader->GetMatrix("Projection")->SetMatrix((float*)&Camera::Projection);

	UINT stride = _vertexbuffer->GetStride();
	UINT offset = _vertexbuffer->GetOffset();

	DEVICECONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DEVICECONTEXT->IASetVertexBuffers(0, 1, _vertexbuffer->GetComPtr().GetAddressOf(), &stride, &offset);
	DEVICECONTEXT->IASetIndexBuffer(_indexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);
	_shader->DrawIndexed(0, 0, _indexBuffer->GetCount(), 0, 0);
}
