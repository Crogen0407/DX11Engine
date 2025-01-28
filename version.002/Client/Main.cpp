#include "pch.h"
#include "Main.h"
#include "Engine/Core.h"
#include "TriangleDemo.h"
#include "QuadDemo.h"
#include "ConstantBufferDemo.h"
#include "CameraDemo.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	CoreDesc desc;
	desc.appName = L"DX11Engine";
	desc.hInstance = hInstance;
	desc.vsync = false;
	desc.hWnd = NULL;
	desc.width = 800;
	desc.height = 600;
	desc.clearColor = Color(0.5f, 0.5f, 0.5f, 0.5f);
	desc.app = make_shared<CameraDemo>();

	CORE->Run(desc);

	return 0;
}