#include "pch.h"
#include "InputManager.h"
void InputManager::Init(HWND hWnd)
{
	_hWnd = hWnd;

	for (int i = 0; i < (int)KEY_TYPE::LAST; ++i)
		_vecKey.push_back(tKeyInfo{KEY_STATE::NONE, false});
}

void InputManager::Update()
{
	//GetActiveWindow(); // 창을 여러개 띄울때 맨 위에있는 윈도우
	HWND hWnd = GetFocus(); // 지금 딱 포커싱한거
	if (hWnd == nullptr)
	{
		for (int i = 0; i < (int)KEY_TYPE::LAST; ++i)
		{
			_vecKey[i].IsPrevCheck = false;
			_vecKey[i].eState = KEY_STATE::NONE;
		}
		return;
	 }
	for (int i = 0; i < (int)KEY_TYPE::LAST; ++i)
	{
		// 키가 눌렸다.
		if (GetAsyncKeyState(_arrVKKey[i]))
		{
			// 이전에 눌렸어
			if (_vecKey[i].IsPrevCheck)
				_vecKey[i].eState = KEY_STATE::PRESS;
			else // 이전에 안눌렸어. 지금 딱!!! 누름
				_vecKey[i].eState = KEY_STATE::DOWN;
			_vecKey[i].IsPrevCheck = true;
		}
		// 키가 안눌렸다.
		else
		{
			// 이전에 눌려있었다.
			if (_vecKey[i].IsPrevCheck)
				_vecKey[i].eState = KEY_STATE::UP;
			else
				_vecKey[i].eState = KEY_STATE::NONE;
			_vecKey[i].IsPrevCheck = false;
		}
	}
	// Mouse
	::GetCursorPos(&_ptMouse); // 마우스 좌표 받기
	// 우리가 가진 윈도우 창 기준으로 좌표 변경
	::ScreenToClient(_hWnd, &_ptMouse);
}
