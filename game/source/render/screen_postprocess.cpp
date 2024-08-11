#include "render/screen_postprocess.hpp"

#include "memory/module.hpp"
#include "views/render_view.hpp"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

decltype(c_screen_postprocess::postprocess_player_view)* screen_postprocess_postprocess_player_view = c_screen_postprocess::postprocess_player_view;
HOOK_DECLARE_CALL(0x00A39F4E, screen_postprocess_postprocess_player_view);

//ADDED BY US
c_rasterizer::e_surface __cdecl c_screen_postprocess::blur_display(float blur_x, float blur_y, int quality_setting) {
	if (c_rasterizer::get_render_target(0) == 29) {
		c_rasterizer::e_surface blur_surface = c_rasterizer::e_surface::_surface_screenshot_display;

		if (c_player_view::get_current())
			blur_surface = static_cast<c_rasterizer::e_surface>(c_player_view::get_current()->get_blur_surface());

		c_rasterizer::set_render_target(0, c_rasterizer::e_surface::_surface_aux_small, -1);
		c_rasterizer::clearf(1, 0xFF000000, 0, 0);
		c_rasterizer::set_color_write_enable(0, 7);

		c_screen_postprocess::copy(
			39,
			blur_surface,
			c_rasterizer::e_surface::_surface_aux_small,
			c_rasterizer::e_sampler_filter_mode::_filter_bilinear,
			c_rasterizer::e_sampler_address_mode::_address_mode_clamp,
			1.0,
			1.0,
			1.0,
			1.0,
			0);

		c_rasterizer::set_color_write_enable(0, 15);

		c_screen_postprocess::gaussian_blur_arbitrary_scaled(
			c_rasterizer::e_surface::_surface_aux_small,
			c_rasterizer::e_surface::_surface_aux_small2,
			blur_x,
			blur_y,
			quality_setting);
	}

	return c_rasterizer::e_surface::_surface_aux_small;
}

void __cdecl c_screen_postprocess::calculate_gaussian_kernel(
	float* out_kernel,
	int kernel_size,
	float a3,
	float radius)
{
	if (radius < 0.0001) {
		csmemset(out_kernel, 0, 4 * kernel_size);

		float v8 = a3;
		if (v8 <= 0.0)
			v8 = 0.0;

		int index = kernel_size - 1;
		if ((kernel_size - 1) > v8)
			index = v8;

		out_kernel[index] = 1.0;
	}
	else {
		float tap_accum = 0.0;
		float radial = 1.0 / (radius * sqrt(2 * M_PI));
		for (int i = 0; i < kernel_size; ++i) {
			float v7 = pow((i - a3), 2.0);
			float v6 = radial * exp(v7 /* ^ _xmm*/);
			float kernel = v6 * (1.0 / (pow(radius, 2.0) * 2.0));

			out_kernel[i] = kernel;
			tap_accum = tap_accum + kernel;
		}

		for (int j = 0; j < kernel_size; ++j)
			out_kernel[j] = (1.0 / tap_accum) * out_kernel[j];
	}
}

void __cdecl c_screen_postprocess::calculate_taps_from_kernel(
	float* kernel,
	vector4d* out_taps,
	int tap_count,
	bool horizontal,
	float a5) {
	for (int i = 0; i < tap_count; ++i) {
		float v7 = kernel[2 * i] + kernel[2 * i + 1];

		float v8 = 0.5;
		if (v7 > 0.0)
			v8 = ((2 * i) - 4.0) - (kernel[2 * i] / v7);

		float v5 = 0.0;
		if (horizontal)
			v5 = v8;
		else
			v5 = a5;

		out_taps[i].i = v5;

		float v6 = 0.0;
		if (horizontal)
			v6 = a5;
		else
			v6 = v8;

		out_taps[i].j = v6;
		out_taps[i].k = v7;
		out_taps[i].l = 0.0;
	}
}

void __cdecl c_screen_postprocess::gaussian_blur_arbitrary(
	c_rasterizer::e_surface src_surface,
	c_rasterizer::e_surface dst_surface,
	float x,
	float y)
{
	float sq_x = pow(x, 2.0);
	float sq_y = pow(y, 2.0);
	float x_accum = 0.0, y_accum = 0.0;

	while (sq_x > (x_accum + 2.5) && sq_y > (y_accum + 2.5)) {
		c_screen_postprocess::gaussian_blur_fixed(src_surface, dst_surface, 1.0, 1.0, 1.0, 1.0);

		x_accum = x_accum + 2.5;
		y_accum = y_accum + 2.5;
	}

	while (sq_x > x_accum || sq_y > y_accum) {
		float x_radius = sq_x - x_accum;
		float y_radius = sq_y - y_accum;

		if (x_radius >= 2.5)
			x_radius = 2.5;

		if (y_radius >= 2.5)
			y_radius = 2.5;

		c_screen_postprocess::gaussian_blur_custom(src_surface, dst_surface, sqrt(x_radius), sqrt(y_radius));

		x_accum = x_accum + x_radius;
		y_accum = y_accum + y_radius;
	}
}

void __cdecl c_screen_postprocess::gaussian_blur_arbitrary_scaled(
	c_rasterizer::e_surface src_surface,
	c_rasterizer::e_surface dst_surface,
	float x,
	float y,
	int quality_setting)
{
	float display_width = c_rasterizer::render_globals.resolution_width;
	float display_height = c_rasterizer::render_globals.resolution_height;
	float backbuffer_width = c_rasterizer::render_globals.back_buffer_width;
	float backbuffer_height = c_rasterizer::render_globals.back_buffer_height;

	if (quality_setting) {
		if (quality_setting == 1) {
			float blur_x = (display_width / 2.0) / backbuffer_width;
			float blur_y = (display_height / 2.0) / backbuffer_height;

			if (blur_x <= 1.0)
				blur_x = 1.0;

			if (blur_y <= 1.0)
				blur_y = 1.0;

			c_screen_postprocess::gaussian_blur_arbitrary(src_surface, dst_surface, x * blur_x, y * blur_y);
		}
		else {
			c_screen_postprocess::gaussian_blur_arbitrary(
				src_surface,
				dst_surface,
				(display_width / backbuffer_width) * x,
				(display_height / backbuffer_height) * y);
		}
	}
	else
		reinterpret_cast<void(__cdecl*)(c_rasterizer::e_surface, c_rasterizer::e_surface)>(0xA60D60)(src_surface, dst_surface);
}

void __cdecl c_screen_postprocess::gaussian_blur_custom(
	c_rasterizer::e_surface src_surface,
	c_rasterizer::e_surface dst_surface,
	float x,
	float y)
{
	float kernel[10];
	csmemset(kernel, 0, sizeof(kernel));

	vector4d kernel_taps[5];
	csmemset(kernel_taps, 0, sizeof(kernel_taps));

	float sq_x = pow(x, 2.0);
	float sq_y = pow(y, 2.0);

	if (sq_x > 1.0)
		c_screen_postprocess::calculate_gaussian_kernel(kernel, 10, 4.5, sqrt(sq_x - 0.25));
	else {
		c_screen_postprocess::calculate_gaussian_kernel(&kernel[1], 9, 4.0, x);
		kernel[0] = 0.0;
	}

	float a5 = 0.5;
	if (sq_y <= 1.0)
		a5 = 0.0;

	c_screen_postprocess::calculate_taps_from_kernel(kernel, kernel_taps, 5, 1, a5);

	c_rasterizer::set_pixel_shader_constant(3, 5, kernel_taps);

	c_screen_postprocess::copy(
		34,
		src_surface,
		dst_surface,
		c_rasterizer::e_sampler_filter_mode::_filter_bilinear,
		c_rasterizer::e_sampler_address_mode::_address_mode_clamp,
		1.0,
		1.0,
		1.0,
		1.0,
		0);

	if (sq_y != sq_x) {
		if (sq_y > 1.0)
			c_screen_postprocess::calculate_gaussian_kernel(kernel, 10, 4.5, sqrt(sq_y - 0.25));
		else {
			c_screen_postprocess::calculate_gaussian_kernel(&kernel[1], 9, 4.0, x);
			kernel[0] = 0.0;
		}
	}

	a5 = 0.5;
	if (sq_x <= 1.0)
		a5 = 0.0;

	c_screen_postprocess::calculate_taps_from_kernel(kernel, kernel_taps, 5, 0, a5);

	c_rasterizer::set_pixel_shader_constant(3, 5, kernel_taps);

	c_screen_postprocess::copy(
		34,
		dst_surface,
		src_surface,
		c_rasterizer::e_sampler_filter_mode::_filter_bilinear,
		c_rasterizer::e_sampler_address_mode::_address_mode_clamp,
		1.0,
		1.0,
		1.0,
		1.0,
		0);
}

void __cdecl c_screen_postprocess::gaussian_blur_fixed(
	c_rasterizer::e_surface src_surface,
	c_rasterizer::e_surface dst_surface,
	float a0,
	float a1,
	float a2,
	float a3)
{
	INVOKE(0x00A60DE0, gaussian_blur_fixed, src_surface, dst_surface, a0, a1, a2, a3);
}

void __cdecl c_screen_postprocess::copy(
	long explicit_shader_index,
	c_rasterizer::e_surface surface_a,
	c_rasterizer::e_surface surface_b,
	c_rasterizer::e_sampler_filter_mode sampler_filter_mode,
	c_rasterizer::e_sampler_address_mode sampler_address_mode,
	real a6,
	real a7,
	real a8,
	real a9,
	real_rectangle2d* bounds)
{
	INVOKE(0x00A60460, c_screen_postprocess::copy, explicit_shader_index, surface_a, surface_b, sampler_filter_mode, sampler_address_mode, a6, a7, a8, a9, bounds);
}

void __cdecl c_screen_postprocess::postprocess_player_view(
	c_camera_fx_values& fx_values,
	render_camera const* camera,
	s_screen_effect_settings& screen_effect_settings,
	e_splitscreen_res splitscreen_res,
	s_observer_depth_of_field const* observer_dof,
	e_output_user_index output_user_index,
	c_rasterizer::e_surface surface)
{
	INVOKE(0x00A61770, c_screen_postprocess::postprocess_player_view, fx_values, camera, screen_effect_settings, splitscreen_res, observer_dof, output_user_index, surface);

	if (render_debug_toggle_default_lightmaps_texaccum == 3)
	{
		c_screen_postprocess::setup_rasterizer_for_postprocess(false);
		c_screen_postprocess::copy(
			c_rasterizer_globals::_explicit_shader_copy_surface,
			c_rasterizer::_surface_accum_LDR,
			c_rasterizer::_surface_disable,
			c_rasterizer::_sampler_filter_mode_unknown1,
			c_rasterizer::_sampler_address_mode_unknown1,
			1.0f,
			1.0f,
			1.0f,
			1.0f,
			NULL);
	}
}

void __cdecl c_screen_postprocess::setup_rasterizer_for_postprocess(bool a1)
{
	INVOKE(0x00A63510, c_screen_postprocess::setup_rasterizer_for_postprocess, a1);
}

