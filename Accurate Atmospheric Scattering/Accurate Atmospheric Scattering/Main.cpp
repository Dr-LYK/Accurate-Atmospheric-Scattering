#include "Atmosphere.h"
#include "Common.h"
#include "GUI.h"
#include "Renderer.h"
#include "Window.h"

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3dcompiler.lib")

void update() {
	GUI::update();
	Atmosphere::update();
	Renderer::update();
}

void render() {
	Renderer::render_frame();
	GUI::render_frame();
	Renderer::present_frame();
}

void clean_up() {
	GUI::clean_up();
}

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE prevInstance,
	LPWSTR cmdLine,
	int cmdShow)
{
	Window::init(hInstance, 960, 540);
	Renderer::init();
	GUI::init();
	Atmosphere::init();

	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
		else
		{
			update();
			render();
		}
	}
	clean_up();
	return 0;
}