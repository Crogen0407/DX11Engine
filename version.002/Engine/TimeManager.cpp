#include "pch.h"
#include "TimeManager.h"
#include "InputManager.h"

void TimeManager::Init(HWND hWnd)
{
	_hWnd = hWnd;
	// 카운트를 측정해서 가져온다.
	::QueryPerformanceCounter(&_llPrevCnt);
	
	// 초당 카운트 횟수(1초당 1000만) 반환
	::QueryPerformanceFrequency(&_llFrequency);
}

void TimeManager::Update()
{
	::QueryPerformanceCounter(&_llCurCnt);
	
	//m_dT  = ;
	// deltatime(변화시간) : 한 프레임에 걸린 시간 
	_unscaledDT = (float)(_llCurCnt.QuadPart - _llPrevCnt.QuadPart)
		/ (float)_llFrequency.QuadPart;

	_dT = _unscaledDT * timeScale;

	_llPrevCnt = _llCurCnt;

	// FPS(Frame Per Second): 1초당 몇 프레임 가냐.
	//1.f / m_dT;
	_framecnt++; // 프레임 체크 횟수를 모아
	_frametime += _dT; // 실제시간을 모아
	if (_frametime >= 1.f) // 1초
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
