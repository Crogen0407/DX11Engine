#include "pch.h"
#include "GlobalTestDemo.h"
#include "GeometryHelper.h"
#include "InputManager.h"
#include "Camera.h"
#include "GameObject.h"
#include "CameraScript.h"
#include "ResourceManager.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "RenderManager.h"

void GlobalTestDemo::Init()
{
	_shader = make_shared<Shader>(L"GlobalTest.fx");

	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform();
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());

	// Object
	_obj = make_shared<GameObject>();
	_obj->GetOrAddTransform();
	_obj->AddComponent(make_shared<MeshRenderer>());
	{
		auto meshRenderer = static_pointer_cast<MeshRenderer>(_obj->GetFixedComponent(ComponentType::MeshRenderer));
		meshRenderer->SetShader(_shader);

		GET_SINGLE(ResourceManager)->Init();
		auto mesh = GET_SINGLE(ResourceManager)->Get<Mesh>(L"Sphere");
		meshRenderer->SetMesh(mesh);

		auto texture = GET_SINGLE(ResourceManager)->Load<Texture>(L"Player", L"..\\Resources\\Textures\\Player.png");
		meshRenderer->SetTexture(texture);
	}

	GET_SINGLE(RenderManager)->Init(_shader);
}

void GlobalTestDemo::Update()
{
	_camera->Update();

	GET_SINGLE(RenderManager)->Update();

	_obj->GetTransform()->SetRotation({ 0, sinf(TIME)*2, 0});
	_obj->Update();
}

void GlobalTestDemo::Render()
{
	
}
