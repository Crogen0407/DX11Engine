#include "pch.h"
#include "Core.h"
#include "GameObject.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "RenderManager.h"
#include "TimeManager.h"

unique_ptr<Core> GCore = make_unique<Core>();

Core::Core() : _hWnd(NULL)
{
}

Core::~Core()
{
}

void Core::Init(HWND hwnd)
{
	cout << "ÁÖ´¨½Ü »ç¶ûÇØ¿ä¢½";

	_hWnd = hwnd;

	_graphics = std::make_shared<Graphics>(_hWnd);

	_sceneManager = make_shared<SceneManager>(_graphics);
	_sceneManager->Init();
	_resourceManager = make_shared<ResourceManager>(_graphics->GetDevice());
	_resourceManager->Init();
	_renderManager = make_shared<RenderManager>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	_renderManager->Init();

	GET_SINGLE(TimeManager)->Init();

	SCENE->LoadScene(L"Test");
}
	
void Core::GameLoop()
{
	Update();
	Render();
}

void Core::Update()
{
	GET_SINGLE(TimeManager)->Update();
	SCENE->Update();
}

void Core::Render()
{
	RENDER->Update(_graphics);
}