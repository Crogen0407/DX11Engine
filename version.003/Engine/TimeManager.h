#pragma once

#define DELTA_TIME				GET_SINGLE(TimeManager)->GetDT()
#define UNSCALED_DELTA_TIME		GET_SINGLE(TimeManager)->GetUnscaledDT()
#define UNSCALED_TIME			GET_SINGLE(TimeManager)->GetUnscaledTime()
#define TIME					GET_SINGLE(TimeManager)->time
class TimeManager
{
	DECLARE_SINGLE(TimeManager);
public:
	void Init(HWND hWnd);
	void Update();
public:
	const float& GetDT() const { return _dT; }
	const float& GetUnscaledDT() const { return _unscaledDT; }
	const float& GetUnscaledTime() const { return _unscaledTime; }
public:
	float time = 0.f;
	float timeScale = 1.f;
private:
	HWND _hWnd;
	// Delta time
	LARGE_INTEGER _llPrevCnt = {};
	LARGE_INTEGER _llCurCnt = {};
	LARGE_INTEGER _llFrequency = {};
	float		  _dT = 0.f;
	float		  _unscaledDT = 0.f;
	float		  _unscaledTime = 0.f;

	// FPS(Frame Per Second)
	UINT		  _fps = 0;
	UINT		  _framecnt = 0;
	float		  _frametime = 0.f;
};

