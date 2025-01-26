#include "pch.h"
#include "Core.h"
#include "GameObject.h"

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
	_pipeline = std::make_shared<Pipeline>(_graphics->GetDeviceContext());
	_object = std::make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
}
	
void Core::GameLoop()
{
	Update();
	Render();
}

void Core::Update()
{
	_object->Update();
}

void Core::Render()
{
	_graphics->RenderBegin();
	{
		_object->Render(_pipeline);
	}
	_graphics->RenderEnd();
}