#pragma once
class GameObject;
class Core
{
public:
	Core();
	~Core();

public:
	void Init(HWND hWnd);
	void GameLoop();

private:
	void Update();
	void Render();

private:
	HWND _hWnd;
	std::shared_ptr<Graphics> _graphics;
	std::shared_ptr<Pipeline> _pipeline;

private:
	std::shared_ptr<GameObject> _object;
};

