#include "render/old_render_debug.hpp"

#include "game/player_mapping.hpp"
#include "input/input_abstraction.hpp"
#include "input/input_windows.hpp"
#include "objects/objects.hpp"
#include "physics/collisions.hpp"
#include "render/render_debug.hpp"
#include "render/views/render_view.hpp"
#include "scenario/scenario.hpp"
#include "structures/structure_bsp_definitions.hpp"
#include "units/bipeds.hpp"

bool debug_structure_markers = false;
bool debug_structure_surface_references = false;
bool debug_structure_soft_ceilings = false;
bool debug_structure_soft_kill = false;
bool debug_structure_slip_surfaces = false;
bool debug_structure_cluster_skies = false;
bool debug_structure_invisible = false;
bool debug_structure = false;
bool debug_structure_automatic = false;
long debug_plane_index = NONE;
bool debug_structure_unique_colors = false;
bool debug_structure_complexity = false;
bool debug_structure_seam_edges = false;
bool debug_instanced_geometry = false;
bool debug_instanced_geometry_bounding_spheres = false;
bool debug_instanced_geometry_names = false;
bool debug_instanced_geometry_vertex_counts = false;
bool debug_instanced_geometry_collision_geometry = false;
bool debug_zone_set_critical_portals = false;
bool debug_structure_water = false;
bool debug_input = false;
bool debug_input_abstraction = false;
bool debug_input_mouse_state = false;
bool debug_player = false;
bool debug_render_freeze = false;
bool debug_camera = false;
bool debug_tangent_space = false;
bool debug_permanent_decals = false;

void render_debug_input()
{
	char raw_data_string[512]{};
	if (debug_input)
	{
		input_get_raw_data_string(raw_data_string, sizeof(raw_data_string) - 1);
		render_debug_string(raw_data_string);
	}

	if (debug_input_abstraction)
	{
		input_abstraction_get_raw_data_string(raw_data_string, sizeof(raw_data_string) - 1);
		render_debug_string(raw_data_string);
	}

	if (debug_input_mouse_state)
	{
		input_mouse_state_get_raw_data_string(raw_data_string, sizeof(raw_data_string) - 1);
		render_debug_string(raw_data_string);
	}
}

void render_debug_player()
{
	// This function is implemented, however the function doesn't actually do much

	if (!debug_player)
		return;

	e_output_user_index user_index = c_player_view::get_current()->get_player_view_output_user_index();
	if (user_index != NONE)
	{
		long unit_index = player_mapping_get_unit_by_output_user(user_index);
		if (biped_datum* biped = (biped_datum*)object_try_and_get_and_verify_type(unit_index, _object_mask_biped))
		{
			if (biped->object.parent_object_index != NONE && biped->unit.parent_seat_index != NONE)
			    unit_index = biped->object.parent_object_index;
		}
		object_try_and_get_and_verify_type(unit_index, _object_mask_vehicle);
	}
}

void render_debug_camera()
{
	if (debug_render_freeze)
	{
		// #TODO: implement
	}

	if (debug_camera || debug_tangent_space)
	{
		// #TODO: implement

		//char buffer[2048]{};
		//csnzprintf(buffer, "point(%01.2f,%01.2f,%01.2f)) cluster(#bsp %d, %d [bsp %d, %d]), sky(attached %d, visible %d)"
		//	#TODO: );
		//status_strings("debug camera", buffer);
	}
}

void render_debug_bsp()
{
	// #TODO: implement
}

void render_debug_structure_decals()
{
	if (!debug_permanent_decals)
		return;

	for (long structure_bsp_index = global_structure_bsp_first_active_index_get();
		structure_bsp_index != NONE;
		structure_bsp_index = global_structure_bsp_next_active_index_get(structure_bsp_index))
	{
		long runtime_decal_index = 0;
		for (structure_runtime_decal& runtime_decal : global_structure_bsp_get(structure_bsp_index)->runtime_decals)
		{
			struct scenario* scenario = global_scenario_get();

			ASSERT(VALID_INDEX(runtime_decal.decal_palette_index, scenario->decal_palette.count()));
			scenario_decal_palette_entry& decal_palette = scenario->decal_palette[runtime_decal.decal_palette_index];

			s_cluster_reference scenario_cluster = scenario_cluster_reference_from_point(&runtime_decal.position);
			structure_bsp const* bsp = scenario_structure_bsp_get(scenario, scenario_cluster.bsp_index);

			ASSERT(VALID_INDEX(scenario_cluster.cluster_index, bsp->clusters.count()));
			structure_cluster& cluster = bsp->clusters[scenario_cluster.cluster_index];

			matrix3x3 matrix{};
			matrix3x3_rotation_from_quaternion(&matrix, &runtime_decal.rotation);

			vector3d vector{};
			scale_vector3d(&vector, -1.0f, &matrix.up);

			real_point3d* position = &runtime_decal.position;
			real_argb_color const* color = global_real_argb_red;

			collision_result collision;
			if (collision_test_vector(_collision_test_environment_flags, &runtime_decal.position, &vector, NONE, NONE, &collision))
			{
				if (cluster.runtime_first_decal_index != 0xFFFF && runtime_decal_index - cluster.runtime_first_decal_index < cluster.runtime_decal_count)
				{
					position = &collision.position;
					color = global_real_argb_yellow;
				}
				else
				{
					position = &collision.position;
					color = global_real_argb_orange;
				}
			}

			render_debug_sphere(true, position, 0.1f, color);

			char const* tag_name = tag_get_name(decal_palette.reference.index);
			char const* name = tag_name_strip_path(tag_name);
			render_debug_string_at_point(&runtime_decal.position, name, global_real_argb_green);

			runtime_decal_index++;
		}
	}
}

bool __cdecl render_debug_lost_camera()
{
	return c_player_view::get_current()->m_location.cluster_reference.bsp_index;
}

real_rgb_color* __cdecl set_real_rgb_color(real_rgb_color* color, real red, real green, real blue)
{
	ASSERT(color);

	color->red = red;
	color->green = green;
	color->blue = blue;

	return color;
}

real_argb_color* __cdecl set_real_argb_color(real_argb_color* color, real alpha, real red, real green, real blue)
{
	ASSERT(color);

	color->alpha = alpha;
	set_real_rgb_color(&color->color, red, green, blue);

	return color;
}

