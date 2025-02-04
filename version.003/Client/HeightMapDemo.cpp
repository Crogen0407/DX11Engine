#include "pch.h"
#include "HeightMapDemo.h"
#include "GeometryHelper.h"
#include "InputManager.h"
#include "Camera.h"
#include "GameObject.h"
#include "CameraScript.h"
#include "ResourceManager.h"

void HeightMapDemo::Init()
{
	_shader = make_shared<Shader>(L"Terrain.fx");

	// Texture
	_heightMap = GET_SINGLE(ResourceManager)->Load<Texture>(L"Height", L"..\\Resources\\Textures\\Terrain\\height.png");
	_texture = GET_SINGLE(ResourceManager)->Load<Texture>(L"Player", L"..\\Resources\\Textures\\Terrain\\grass.jpg");

	const UINT width = _heightMap->GetSize().x;
	const UINT height = _heightMap->GetSize().y;

	const DirectX::ScratchImage& info = _heightMap->GetInfo();
	uint8_t* pixelBuffer = info.GetPixels();

	// Object
	_geometry = make_shared<Geometry<VertexTextureData>>();
	GeometryHelper::CreateGrid(_geometry, width, height);

	// CPU
	{
		vector<VertexTextureData>& v = const_cast<vector<VertexTextureData>&>(_geometry->GetVertices());

		for (int z = 0; z < height; z++)
		{
			for (int x = 0; x < width; x++)
			{
				int idx = width * z + x;
				UINT height = pixelBuffer[idx] / 255.f * 25.f;
				v[idx].position.y = height; // 높이 보정
			}
		}
	}

	_vertexbuffer = make_shared<VertexBuffer>();
	_vertexbuffer->Create(_geometry->GetVertices());
	_indexBuffer = make_shared<IndexBuffer>();
	_indexBuffer->Create(_geometry->GetIndices());

	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform();
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());

	_camera->GetTransform()->SetPosition({ 0, 5, 0});
	_camera->GetTransform()->SetRotation({ 25.f, 0.f, 0.f });
}

void HeightMapDemo::Update()
{
	_camera->Update();
}

void HeightMapDemo::Render()
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
