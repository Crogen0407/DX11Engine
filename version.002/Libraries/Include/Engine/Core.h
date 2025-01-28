#pragma once

struct CoreDesc
{
	shared_ptr<class IExecute> app = nullptr;
	wstring appName = L"GameCoding";
	HINSTANCE hInstance = 0;
	HWND hWnd = 0;
	float width = 800;
	float height = 600;
	bool vsync = false;
	bool windowed = true;
	Color clearColor = Color(0.5f, 0.5f, 0.5f, 0.5f);
};

class Core
{
	DECLARE_SINGLE(Core);
public:
	WPARAM Run(CoreDesc& desc);

	CoreDesc& GetCoreDesc() { return _desc; }

private:
	ATOM MyRegisterClass();
	BOOL InitInstance(int cmdShow);

	void Update();

	static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
	
private:
	CoreDesc _desc;
};

