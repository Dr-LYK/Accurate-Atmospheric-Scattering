#include "Common.h"

#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_dx11.h"

#include "Store.h"
#include "Window.h"
#include "Renderer.h"
#include "Atmosphere.h"

namespace Store
{
	static Data data;
	static ImVec2 last_mouse_pos;
	static const float mouse_pos_scale = 1.0f / 500.0f;

	void init()
	{
		ImGui::CreateContext();
		ImGui_ImplDX11_Init((void*)Window::get_handle(), Renderer::get_device().Get(), Renderer::get_device_context().Get());
	}

	void update()
	{
		ImGui_ImplDX11_NewFrame();
		ImVec2 mouse_pos = ImGui::GetMousePos();
		ImGuiIO& io = ImGui::GetIO();
		bool is_mouse_captured = io.WantCaptureMouse;
		bool is_ctrl_pressed = io.KeyCtrl;
		bool is_left_mouse_button_pressed = ImGui::IsMouseDown(0);
		if (!is_mouse_captured && is_left_mouse_button_pressed)
		{
			float view_zenith_angle_in_radians = XMConvertToRadians(data.view_zenith_angle_in_degrees);
			view_zenith_angle_in_radians += (last_mouse_pos.y - mouse_pos.y) * mouse_pos_scale;
			view_zenith_angle_in_radians = XMMax(0.f, XMMin(XM_PIDIV2, view_zenith_angle_in_radians));
			data.view_zenith_angle_in_degrees = XMConvertToDegrees(view_zenith_angle_in_radians);
			float view_azimuth_angle_in_radians = XMConvertToRadians(data.view_azimuth_angle_in_degrees);
			view_azimuth_angle_in_radians += (last_mouse_pos.x - mouse_pos.x) * mouse_pos_scale;
			data.view_azimuth_angle_in_degrees = XMConvertToDegrees(view_azimuth_angle_in_radians);
		}
		last_mouse_pos = mouse_pos;
		if (io.MouseWheel < 0.0) { data.view_distance *= 1.05f; }
		else if (io.MouseWheel > 0.0) { data.view_distance /= 1.05f; };

		{
			ImVec2 window_pos = ImVec2(io.DisplaySize.x - 100, 0);
			ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always, ImVec2(0, 0));
			ImGui::SetNextWindowBgAlpha(0.3f);

			ImGui::Begin("Information", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings);
			ImGui::PushItemWidth(100);
			
			ImGui::Text("Calendar: ");
			ImGui::Text("Day: %d", data.day);
			ImGui::Text("Year: %d", data.year);

			ImGui::Separator();

			ImGui::Text("Details: ");
			ImGui::Text("Sun azimuth angle: %f", data.sun_azimuth_angle_in_degrees);
			ImGui::Text("Sun zenith angle: %f", data.sun_zenith_angle_in_degrees);

			ImGui::Separator();

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::End();
		}
	}

	void render_frame()
	{
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	void clean_up()
	{
		ImGui_ImplDX11_Shutdown();
		ImGui::DestroyContext();
	}

	Data& get_data()
	{
		return data;
	}
}