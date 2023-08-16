#include "render/views/render_player_view.hpp"

#include "render/views/render_view.hpp"

void __cdecl c_player_view::get_player_render_camera_orientation(real_matrix4x3* camera)
{
	//INVOKE(0x00A39640, get_player_render_camera_orientation, camera);

	ASSERT(camera);
	ASSERT(c_player_view::x_current_player_view, "cannot get the render camera when not in the player view render loop");

	render_camera const* rasterizer_camera = c_player_view::x_current_player_view->get_rasterizer_camera();

	camera->center = rasterizer_camera->position;
	camera->matrix.forward = rasterizer_camera->forward;
	camera->matrix.up = rasterizer_camera->up;
	cross_product3d(&camera->matrix.up, &camera->matrix.forward, &camera->matrix.left);
	camera->scale = 1.0f;
}
