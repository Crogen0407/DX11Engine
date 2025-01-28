#include "pch.h"
#include "TimeManager.h"
#include "InputManager.h"

void TimeManager::Init(HWND hWnd)
{
	_hWnd = hWnd;
	// ī��Ʈ�� �����ؼ� �����´�.
	::QueryPerformanceCounter(&_llPrevCnt);
	
	// �ʴ� ī��Ʈ Ƚ��(1�ʴ� 1000��) ��ȯ
	::QueryPerformanceFrequency(&_llFrequency);
}

void TimeManager::Update()
{
	::QueryPerformanceCounter(&_llCurCnt);
	
	//m_dT  = ;
	// deltatime(��ȭ�ð�) : �� �����ӿ� �ɸ� �ð� 
	_unscaledDT = (float)(_llCurCnt.QuadPart - _llPrevCnt.QuadPart)
		/ (float)_llFrequency.QuadPart;

	_dT = _unscaledDT * timeScale;

	_llPrevCnt = _llCurCnt;

	// FPS(Frame Per Second): 1�ʴ� �� ������ ����.
	//1.f / m_dT;
	_framecnt++; // ������ üũ Ƚ���� ���
	_frametime += _dT; // �����ð��� ���
	if (_frametime >= 1.f) // 1��
	{
		_fps = (UINT)(_framecnt / _frametime);
		_frametime = 0.f;
		_framecnt = 0;
		//wstring strfps = std::to_wstring(m_fps);
		//wstring strdt = std::to_wstring(m_dT);
		//wstring str = L"FPS : " + strfps  +
		//			 L" DT: " + strdt;
		//TextOut(GET_SINGLE(Core)->GetMainDC(),0,0, 
		//		str.c_str(),str.length());
		//std::format();
		//POINT mousepos = GET_SINGLE(InputManager)->GetMousePos();
		Vec2 mousepos = GET_MOUSEPOS;
		static wchar_t buf[100] = {};
		swprintf_s(buf, L"FPS: %d, DT: %f, Mouse: (%d, %d)",_fps, _dT
										,mousepos.x, mousepos.y);
		::SetWindowText(_hWnd
						, buf);
	}

	time += _dT;
	_unscaledTime += _unscaledDT;
}
