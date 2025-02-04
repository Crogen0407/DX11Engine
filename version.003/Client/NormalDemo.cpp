#include "pch.h"
#include "NormalDemo.h"
#include "GeometryHelper.h"
#include "InputManager.h"
#include "Camera.h"
#include "GameObject.h"
#include "CameraScript.h"
#include "ResourceManager.h"

void NormalDemo::Init()
{
	_shader = make_shared<Shader>(L"Normal.fx");

	// Texture
	_texture = GET_SINGLE(ResourceManager)->Load<Texture>(L"Player", L"..\\Resources\\Textures\\Player.png");

	// Object
	_geometry = make_shared<Geometry<VertexTextureNormalData>>();
	GeometryHelper::CreateSphere(_geometry);

	_vertexbuffer = make_shared<VertexBuffer>();
	_vertexbuffer->Create(_geometry->GetVertices());
	_indexBuffer = make_shared<IndexBuffer>();
	_indexBuffer->Create(_geometry->GetIndices());

	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform();
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());
}

void NormalDemo::Update()
{
	_camera->Update();
}

void NormalDemo::Render()
{
	_shader->GetMatrix("World")->SetMatrix((float*)&_world);
	_shader->GetMatrix("View")->SetMatrix((float*)&Camera::View);
	_shader->GetMatrix("Projection")->SetMatrix((float*)&Camera::Projection);
	_shader->GetSRV("Texture0")->SetResource(_texture->GetComPtr().Get());
	_shader->GetVector("LightDir")->SetFloatVector((float*)&_lightDir);
	UINT stride = _vertexbuffer->GetStride();
	UINT offset = _vertexbuffer->GetOffset();

	DEVICECONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DEVICECONTEXT->IASetVertexBuffers(0, 1, _vertexbuffer->GetComPtr().GetAddressOf(), &stride, &offset);
	DEVICECONTEXT->IASetIndexBuffer(_indexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);
	_shader->DrawIndexed(0, 0, _indexBuffer->GetCount(), 0, 0);
}
