#include "Common.h"

#include <thread>
#include <chrono>

#include "Store.h"
#include "Window.h"
#include "Renderer.h"
#include "Atmosphere.h"

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3dcompiler.lib")

bool clear = false;

void update()
{
	Store::update();
	Atmosphere::update();
	Renderer::update();
}

void render()
{
	Renderer::render_frame();
	Store::render_frame();
	Renderer::present_frame();
}

void clean_up()
{
	clear = true;
	Store::clean_up();
}

void timer_init()
{
	clear = false;
	std::thread t([=]()
	{
		while (true)
		{
			if (clear) return;
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			if (clear) return;
			Renderer::update_sun();
		}
	});
	t.detach();
}

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE prevInstance,
	LPWSTR cmdLine,
	int cmdShow)
{
	Window::init(hInstance, 960, 540);
	Renderer::init();
	Store::init();
	Atmosphere::init();
	timer_init();

	MSG msg = { 0 };
	while (msg.message != WM_QUIT) {
		if (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
		else {
			update();
			render();
		}
	}
	clean_up();
	return 0;
}