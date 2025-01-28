#include "pch.h"
#include "TextureDemo.h"
#include "GeometryHelper.h"
#include "InputManager.h"
#include "Camera.h"
#include "GameObject.h"
#include "CameraScript.h"
#include "ResourceManager.h"

void TextureDemo::Init()
{
	_shader = make_shared<Shader>(L"Texture.fx");

	_geometry = make_shared<Geometry<VertexTextureData>>();
	GeometryHelper::CreateGrid(_geometry, 10, 10);

	_vertexbuffer = make_shared<VertexBuffer>();
	_vertexbuffer->Create(_geometry->GetVertices());

	_indexBuffer = make_shared<IndexBuffer>();
	_indexBuffer->Create(_geometry->GetIndices());

	// Camera
	_camera = make_shared<GameObject>(DEVICE, DEVICECONTEXT);
	_camera->GetOrAddTransform();
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());
	_camera->GetTransform()->SetPosition({ 0, 0, -10 });

	_texture = GET_SINGLE(ResourceManager)->Load<Texture>(L"Player", L"..\\Resources\\Textures\\Player.png");
	_camera->Start();
}

void TextureDemo::Update()
{
	_camera->Update();
}

void TextureDemo::Render()
{
	_shader->GetMatrix("World")->SetMatrix((float*)&_world);
	_shader->GetMatrix("View")->SetMatrix((float*)&Camera::View);
	_shader->GetMatrix("Projection")->SetMatrix((float*)&Camera::Projection);
	_shader->GetSRV("Texture0")->SetResource(_texture->GetComPtr().Get());

	UINT stride = _vertexbuffer->GetStride();
	UINT offset = _vertexbuffer->GetOffset();

	DEVICECONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DEVICECONTEXT->IASetVertexBuffers(0, 1, _vertexbuffer->GetComPtr().GetAddressOf(), &stride, &offset);
	DEVICECONTEXT->IASetIndexBuffer(_indexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);
	_shader->DrawIndexed(0, 0, _indexBuffer->GetCount(), 0, 0);
}
