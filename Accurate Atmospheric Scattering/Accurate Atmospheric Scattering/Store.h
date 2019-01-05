#pragma once

struct ID3D11Device;
struct ID3D11DeviceContext;
namespace Atmosphere { enum Luminance; }

namespace Store
{
	typedef struct Data {

		float view_zenith_angle_in_degrees = 85.0f;
		float view_azimuth_angle_in_degrees = 0.0f;
		float view_distance = 10000.0f;
		float sun_zenith_angle_in_degrees = 0.0f;
		float sun_azimuth_angle_in_degrees = 180.0f;
		float exposure = 10.0f;
		bool do_white_balance = true;

		Atmosphere::Luminance use_luminance;
		bool use_ozone_layer = true;
		bool use_constant_solar_spectrum = false;
		bool use_half_precision = false;

		bool debug_dump_textures = false;

		unsigned int day = 1;
		unsigned int year = 1;
	} Data;

	void init();
	void update();
	void render_frame();
	void clean_up();

	Data& get_data();
}