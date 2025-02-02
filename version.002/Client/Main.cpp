#include "pch.h"
#include "Main.h"
#include "Engine/Core.h"
#include "TriangleDemo.h"
#include "QuadDemo.h"
#include "ConstantBufferDemo.h"
#include "CameraDemo.h"
#include "TextureDemo.h"
#include "SamplerDemo.h"
#include "HeightMapDemo.h"
#include "NormalDemo.h"
#include "MeshDemo.h"
#include "GlobalTestDemo.h"
#include "DepthStencilDemo.h"
#include "LightingDemo.h"
#include "MaterialDemo.h"
#include "NormalMappingDemo.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	CoreDesc desc;
	desc.appName = L"Demo";
	desc.hInstance = hInstance;
	desc.vsync = false;
	desc.hWnd = NULL;
	desc.width = 800;
	desc.height = 600;
	desc.clearColor = Color(0.f, 0.f, 0.f, 0.f);
	desc.app = make_shared<NormalMappingDemo>();

	CORE->Run(desc);

	return 0;
}