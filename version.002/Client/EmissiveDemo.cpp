#include "pch.h"
#include "EmissiveDemo.h"
#include "GeometryHelper.h"
#include "InputManager.h"
#include "Camera.h"
#include "GameObject.h"
#include "CameraScript.h"
#include "ResourceManager.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "RenderManager.h"

void EmissiveDemo::Init()
{
	_shader = make_shared<Shader>(L"Lighting_Emissive.fx");
	GET_SINGLE(ResourceManager)->Init();

	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform()->SetPosition({0, 0, -10});
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());

	// Object
	_obj = make_shared<GameObject>();
	_obj->GetOrAddTransform()->SetPosition({1, 0, 0});
	_obj->AddComponent(make_shared<MeshRenderer>());
	{
		auto meshRenderer = static_pointer_cast<MeshRenderer>(_obj->GetFixedComponent(ComponentType::MeshRenderer));
		meshRenderer->SetShader(_shader);

		auto mesh = GET_SINGLE(ResourceManager)->Get<Mesh>(L"Sphere");
		meshRenderer->SetMesh(mesh);

		auto texture = GET_SINGLE(ResourceManager)->Load<Texture>(L"Player", L"..\\Resources\\Textures\\Player.png");
		meshRenderer->SetTexture(texture);
	}

	_obj2 = make_shared<GameObject>();
	_obj2->GetOrAddTransform()->SetPosition({0, 0, 2});
	_obj2->AddComponent(make_shared<MeshRenderer>());
	{
		auto meshRenderer = static_pointer_cast<MeshRenderer>(_obj2->GetFixedComponent(ComponentType::MeshRenderer));
		meshRenderer->SetShader(_shader);

		auto mesh = GET_SINGLE(ResourceManager)->Get<Mesh>(L"Cube");
		meshRenderer->SetMesh(mesh);

		auto texture = GET_SINGLE(ResourceManager)->Load<Texture>(L"Player", L"..\\Resources\\Textures\\Player.png");
		meshRenderer->SetTexture(texture);
	}

	GET_SINGLE(RenderManager)->Init(_shader);
}

void EmissiveDemo::Update()
{
	_camera->Update();

	GET_SINGLE(RenderManager)->Update();

	{
		Vec4 materialDiffuse(1.f);
		_shader->GetVector("MaterialEmissive")->SetFloatVector((float*)&materialDiffuse);
		_obj->Update();
	}
	{
		Vec4 materialDiffuse(1.f);
		_shader->GetVector("MaterialEmissive")->SetFloatVector((float*)&materialDiffuse);
		_obj2->Update();
	}
}

void EmissiveDemo::Render()
{
	
}
