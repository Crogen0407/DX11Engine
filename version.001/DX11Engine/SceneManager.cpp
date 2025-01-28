#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "Core.h"
#include "Mesh.h"
#include "Animator.h"

SceneManager::SceneManager(shared_ptr<Graphics> graphics)
	: _graphics(graphics)
{
}

void SceneManager::Init()
{
	if (_activeScene == nullptr)
		return;

	_activeScene->Awake();
	_activeScene->Start();
}

void SceneManager::Update()
{
	if (_activeScene == nullptr)
		return;

	_activeScene->FixedUpdate();
	_activeScene->Update();
	_activeScene->LateUpdate();
}

void SceneManager::LoadScene(wstring sceneName)
{
	_activeScene = LoadTestScene();
	Init();
}

#include "CameraMove.h"

shared_ptr<Scene> SceneManager::LoadTestScene()
{
	shared_ptr<Scene> scene = make_shared<Scene>();

	auto camera = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	{
		camera->GetOrAddTransform();
		camera->AddComponent(make_shared<Camera>());
		camera->AddComponent(make_shared<CameraMove>());
		scene->AddGameObject(camera);
	}

	auto object = std::make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	{
		object->GetOrAddTransform();
		auto meshRenderer = make_shared<MeshRenderer>(_graphics->GetDevice(), _graphics->GetDeviceContext());
		auto material = RESOURCES->Get<Material>(L"Default");
		auto mesh = RESOURCES->Get<Mesh>(L"Quad");
		meshRenderer->SetMaterial(material);
		meshRenderer->SetMesh(mesh);

		object->AddComponent(meshRenderer);
		scene->AddGameObject(object);
	}

	{
		auto animator = make_shared<Animator>();
		object->AddComponent(animator);
		auto anim = RESOURCES->Get<Animation>(L"Enemy06_Idle");
		animator->SetAnimation(anim);
	}

	return scene;
}
