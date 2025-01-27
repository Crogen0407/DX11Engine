#pragma once
class GameObject;
class SceneManager;
class ResourceManager;
class RenderManager;

class Core
{
public:
	Core();
	~Core();

public:
	void Init(HWND hWnd);
	void GameLoop();
	void Update();
	void Render();

	shared_ptr<SceneManager> GetSceneManager() { return _sceneManager; }
	shared_ptr<ResourceManager> GetResourceManager() { return _resourceManager; }
	shared_ptr<RenderManager> GetRenderManager() { return _renderManager; }

	HWND GetHWnd() { return _hWnd; }

private:
	HWND _hWnd;
	shared_ptr<Graphics> _graphics;

private:
	shared_ptr<SceneManager> _sceneManager;
	shared_ptr<ResourceManager> _resourceManager;
	shared_ptr<RenderManager> _renderManager;
};

extern unique_ptr<Core> GCore;