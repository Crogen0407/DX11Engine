#pragma once


enum class KEY_TYPE
{
	LEFT, RIGHT, UP, DOWN,
	Q, W, E, R, T, Y, U, I, O, P,
	A, S, D, F, G, H, J, K, L,
	Z, X, C, V, B, N, M,
	CTRL, LALT, LSHIFT, SPACE,
	ENTER, TAB, ESC, LBUTTON, RBUTTON,
	NUM_1, NUM_2, LAST
	// LAST�ǹ�: ���̶�� ���̾�
};
enum class KEY_STATE
{					// HOLD
	NONE, DOWN, UP, PRESS, END
};
struct tKeyInfo
{
	KEY_STATE eState;
	bool IsPrevCheck;
};

#define GET_MOUSEPOS			GET_SINGLE(InputManager)->GetMousePos()
#define GET_BUTTON(key)			GET_SINGLE(InputManager)->GetKey(key) == KEY_STATE::PRESS
#define GET_BUTTONDOWN(key)		GET_SINGLE(InputManager)->GetKey(key) == KEY_STATE::DOWN
#define GET_BUTTONUP(key)		GET_SINGLE(InputManager)->GetKey(key) == KEY_STATE::UP

class InputManager
{
	DECLARE_SINGLE(InputManager);
public:
	void Init(HWND hWnd);
	void Update();
	const KEY_STATE& GetKey(KEY_TYPE _eKey) const
	{
		return _vecKey[(int)_eKey].eState;
	}
	const Vec2& GetMousePos() const
	{
		Vec2 mousePosVec;
		mousePosVec.x = _ptMouse.x;
		mousePosVec.y = _ptMouse.y;
		return mousePosVec;
	}
private:
	HWND _hWnd;
	POINT			 _ptMouse = {};
	vector<tKeyInfo> _vecKey;
	int				 _arrVKKey[(int)KEY_TYPE::LAST] =
	{ VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN, 'Q','W','E','R',
	'T','Y','U','I','O','P',
	'A','S','D','F','G','H','J','K','L',
	'Z','X','C','V','B','N','M',
	VK_CONTROL, VK_LMENU, VK_LSHIFT, VK_SPACE,
		VK_RETURN, VK_TAB, VK_ESCAPE,
		VK_LBUTTON, VK_RBUTTON,'1','2' };
};

