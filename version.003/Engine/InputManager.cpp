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
	//GetActiveWindow(); // â�� ������ ��ﶧ �� �����ִ� ������
	HWND hWnd = GetFocus(); // ���� �� ��Ŀ���Ѱ�
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
		// Ű�� ���ȴ�.
		if (GetAsyncKeyState(_arrVKKey[i]))
		{
			// ������ ���Ⱦ�
			if (_vecKey[i].IsPrevCheck)
				_vecKey[i].eState = KEY_STATE::PRESS;
			else // ������ �ȴ��Ⱦ�. ���� ��!!! ����
				_vecKey[i].eState = KEY_STATE::DOWN;
			_vecKey[i].IsPrevCheck = true;
		}
		// Ű�� �ȴ��ȴ�.
		else
		{
			// ������ �����־���.
			if (_vecKey[i].IsPrevCheck)
				_vecKey[i].eState = KEY_STATE::UP;
			else
				_vecKey[i].eState = KEY_STATE::NONE;
			_vecKey[i].IsPrevCheck = false;
		}
	}
	// Mouse
	::GetCursorPos(&_ptMouse); // ���콺 ��ǥ �ޱ�
	// �츮�� ���� ������ â �������� ��ǥ ����
	::ScreenToClient(_hWnd, &_ptMouse);
}
