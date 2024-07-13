#pragma once

#include "rasterizer/rasterizer.hpp"

enum e_splitscreen_res;
enum e_output_user_index;

struct c_camera_fx_values;
struct render_camera;
struct s_screen_effect_settings;
struct s_observer_depth_of_field;

struct c_screen_postprocess
{
	//ADDED BY US

	static c_rasterizer::e_surface __cdecl blur_display(
		float blur_x,
		float blur_y,
		int quality_setting);

	static void __cdecl calculate_gaussian_kernel(
		float* out_kernel,
		int kernel_size,
		float a3,
		float radius);

	static void __cdecl calculate_taps_from_kernel(
		float* kernel,
		vector4d* out_taps,
		int tap_count,
		bool horizontal,
		float a5);

	static void __cdecl gaussian_blur_arbitrary(
		c_rasterizer::e_surface src_surface,
		c_rasterizer::e_surface dst_surface,
		float x,
		float y);

	static void __cdecl gaussian_blur_arbitrary_scaled(
		c_rasterizer::e_surface src_surface,
		c_rasterizer::e_surface dst_surface,
		float x,
		float y,
		int quality_setting);

	static void __cdecl gaussian_blur_custom(
		c_rasterizer::e_surface src_surface,
		c_rasterizer::e_surface dst_surface,
		float x,
		float y);

	static void __cdecl gaussian_blur_fixed(
		c_rasterizer::e_surface src_surface,
		c_rasterizer::e_surface dst_surface,
		float a0,
		float a1,
		float a2,
		float a3);

	static void __cdecl copy(
		long explicit_shader_index,
		c_rasterizer::e_surface surface_a,
		c_rasterizer::e_surface surface_b,
		c_rasterizer::e_sampler_filter_mode sampler_filter_mode,
		c_rasterizer::e_sampler_address_mode sampler_address_mode,
		real a6,
		real a7,
		real a8,
		real a9,
		real_rectangle2d* bounds);

	static void __cdecl postprocess_player_view(
		c_camera_fx_values& fx_values,
		render_camera const* camera,
		s_screen_effect_settings& screen_effect_settings,
		e_splitscreen_res splitscreen_res,
		s_observer_depth_of_field const* observer_dof,
		e_output_user_index output_user_index,
		c_rasterizer::e_surface surface);

	static void __cdecl setup_rasterizer_for_postprocess(bool a1);
};

