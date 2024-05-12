#include "ai/ai_debug.hpp"

#include "ai/actor_perception.hpp"
#include "ai/actor_stimulus.hpp"
#include "ai/actors.hpp"
#include "ai/behavior.hpp"
#include "cache/cache_files.hpp"
#include "camera/observer.hpp"
#include "game/player_mapping.hpp"
#include "interface/interface.hpp"
#include "interface/interface_constants.hpp"
#include "memory/thread_local.hpp"
#include "objects/objects.hpp"
#include "render/render_debug.hpp"
#include "text/draw_string.hpp"
#include "units/dialogue_definitions.hpp"
#include "units/units.hpp"

#include <climits>

real_point3d global_ai_debug_drawstack_next_position;
real global_ai_debug_drawstack_height;
real_point3d global_ai_debug_drawstack_last_position;

short global_ai_debug_string_position = 0;

//path_debug_storage* actor_path_debug_array;
//actor_debug_info* actor_debug_array;
//ai_debug_state ai_debug;

bool g_ai_render = false;
bool g_ai_render_firing_positions_all = false;
bool g_ai_render_lineoffire = false;
bool g_ai_render_lineofsight = false;
bool g_ai_render_ballistic_lineoffire = false;
long g_ai_debug_selected_actor_unit_index = NONE;
long g_ai_debug_selected_actor_index = NONE;
bool g_ai_debug_path = false;
bool g_ai_render_paths_failed = false;
bool g_ai_render_aiming_validity = false;
bool g_ai_render_all_actors = false;
bool g_ai_render_dialogue = false;
bool g_ai_render_dialogue_queue = false;
bool g_ai_render_dialogue_player_weights = false;
bool g_ai_render_speech = false;
bool g_ai_print_speech = false;
bool g_ai_render_spatial_effects = false;
bool g_ai_render_clumps = false;
bool g_ai_render_clump_props = false;
bool g_ai_render_clump_props_all = false;
bool g_ai_render_decisions = false;
bool g_ai_render_decisions_all = false;
bool g_ai_render_behavior_stack_all = false;
bool g_ai_render_character_names = false;
bool g_ai_render_stimuli = false;
bool g_ai_render_sectors = false;
bool g_ai_render_sector_geometry_errors = false;
long g_ai_render_link_specific = 0;
bool g_ai_render_links = false;
bool g_ai_render_user_hints = false;
bool g_ai_render_hints = false;
bool g_ai_render_object_hints_all = false;
bool g_ai_render_object_hints = false;
bool g_ai_render_object_properties = false;
bool g_ai_render_sector_bsps = false;
bool g_ai_render_giant_sector_bsps = false;
bool g_ai_render_sector_link_errors = false;
bool g_ai_render_intersection_links = false;
bool g_ai_render_non_walkable_sectors = false;
bool g_ai_render_threshold_links = false;
bool g_ai_render_orders = false;
bool g_ai_render_suppress_combat = false;
bool g_ai_render_objectives = false;
bool g_ai_render_strength = false;
bool g_ai_debug_tracking_data = false;
bool g_ai_debug_perception_data = false;
bool g_ai_debug_combat_status = false;
bool g_ai_render_tracked_props_all = false;
bool g_ai_render_targets_all = false;
bool g_ai_render_joint_behaviors = false;
bool g_ai_render_flocks = false;
bool g_ai_render_command_scripts = false;
bool g_ai_render_dialogue_variants = false;
bool g_ai_render_vehicle_interest = false;
bool g_ai_render_player_battle_vector = false;
bool g_ai_render_player_needs_vehicle = false;
bool g_ai_render_mission_critical = false;

void __cdecl ai_debug_render()
{
	TLS_DATA_GET_VALUE_REFERENCE(ai_globals);
	TLS_DATA_GET_VALUE_REFERENCE(actor_data);
	
	bool flag = g_ai_render
		&& (g_ai_render_firing_positions_all
		|| g_ai_render_lineoffire
		|| g_ai_render_lineofsight
		|| g_ai_render_ballistic_lineoffire
		|| g_ai_debug_selected_actor_unit_index != NONE && (g_ai_debug_selected_actor_index == NONE || g_ai_render_all_actors)
		|| g_ai_debug_selected_actor_index != NONE && !g_ai_render_all_actors
		|| g_ai_debug_path
		|| g_ai_render_paths_failed
		|| g_ai_render_aiming_validity
		|| g_ai_render_all_actors
		|| g_ai_render_dialogue
		|| g_ai_render_dialogue_queue
		|| g_ai_render_dialogue_player_weights
		|| g_ai_render_speech
		|| g_ai_print_speech
		|| g_ai_render_spatial_effects
		|| g_ai_render_clumps
		|| g_ai_render_clump_props
		|| g_ai_render_clump_props_all
		|| g_ai_render_decisions
		|| g_ai_render_decisions_all
		|| g_ai_render_behavior_stack_all
		|| g_ai_render_stimuli
		|| g_ai_render_sectors
		|| g_ai_render_sector_geometry_errors
		|| g_ai_render_link_specific != NONE
		|| g_ai_render_links
		|| g_ai_render_user_hints
		|| g_ai_render_hints
		|| g_ai_render_object_hints_all
		|| g_ai_render_object_hints
		|| g_ai_render_object_properties
		|| g_ai_render_sector_bsps
		|| g_ai_render_giant_sector_bsps
		|| g_ai_render_sector_link_errors
		|| g_ai_render_intersection_links
		|| g_ai_render_non_walkable_sectors
		|| g_ai_render_threshold_links
		|| g_ai_render_orders
		|| g_ai_render_suppress_combat
		|| g_ai_render_objectives
		|| g_ai_render_strength
		|| g_ai_debug_tracking_data
		|| g_ai_debug_perception_data
		|| g_ai_debug_combat_status
		|| g_ai_render_tracked_props_all
		|| g_ai_render_targets_all
		|| g_ai_render_joint_behaviors
		|| g_ai_render_flocks
		|| g_ai_render_command_scripts
		|| g_ai_render_dialogue_variants
		|| g_ai_render_vehicle_interest
		|| g_ai_render_player_battle_vector);
	
	//main_set_single_thread_request_flag(2, g_dialogue_debug_enabled | flag);
	if (!actor_datum_available_to_current_thread() || !ai_globals->__unknown1)
		return;
	
	short_rectangle2d bounds{};
	interface_get_current_display_settings(NULL, NULL, NULL, &bounds);
	global_ai_debug_string_position = bounds.y1 - 20;
	//dword_143C86DD8 = (dword_143C86DD8 + 1) % 1000;
	if (g_ai_debug_selected_actor_index != NONE)
	{
		actor_datum* actor = (actor_datum*)datum_get(*actor_data, g_ai_debug_selected_actor_index);
		g_ai_debug_selected_actor_unit_index = actor->meta.unit_index;
	}
	
	//if (g_ai_debug)
	//	ai_debug_select_this_actor();
	
	if (g_ai_render)
	{
		//if (g_ai_render_firing_positions_all)
		//	ai_debug_render_all_firing_positions();

		//if (g_ai_render_lineoffire)
		//	ai_debug_render_lineoffire();

		//if (g_ai_render_lineofsight)
		//	ai_debug_render_lineofsight();

		//if (g_ai_render_ballistic_lineoffire)
		//	ai_debug_render_ballistic_lineoffire();

		//if (g_ai_debug_selected_actor_unit_index != NONE && (g_ai_debug_selected_actor_index == NONE || g_ai_render_all_actors))
		//	ai_debug_render_squad_members(g_ai_debug_selected_actor_unit_index);

		//if (g_ai_debug_selected_actor_index != NONE && !ai_render_all_actors)
		//	ai_debug_render_actor(g_ai_debug_selected_actor_index, 1u, 0i64);

		//if (g_ai_debug_path)
		//	ai_debug_render_path();

		//if (g_ai_render_paths_failed)
		//	ai_debug_render_paths_failed();

		//if (g_ai_render_all_actors)
		//	ai_debug_render_all_actors(g_ai_render_inactive_actors);

		//if (g_ai_render_dialogue)
		//	ai_debug_dialogue();

		//if (g_ai_render_dialogue_queue)
		//	ai_dialogue_render_queue();

		if (g_ai_render_dialogue_player_weights)
			ai_dialogue_render_player_weights();

		//if (g_ai_render_speech_enabled || g_ai_print_speech)
		//	ai_debug_render_speech();

		//if (g_ai_render_spatial_effects)
		//	ai_debug_render_spatial_effects();

		//if (g_ai_render_clumps_enabled || g_ai_render_clump_props_enabled || g_ai_render_clump_dialogue || g_ai_render_clump_props_all)
		//	ai_debug_render_clumps();

		//if (g_ai_render_decisions)
		//	ai_debug_render_decisions(0);

		//if (g_ai_render_decisions_all)
		//	ai_debug_render_decisions(1);

		if (g_ai_render_behavior_stack_all)
			ai_debug_render_behavior_stacks_all();

		if (g_ai_render_character_names)
			ai_debug_render_character_names();
	
		if (g_ai_render_stimuli)
			stimuli_debug();
	
		//if (g_ai_render_sectors)
		//	ai_debug_render_sectors();

		//if (g_ai_render_sector_geometry_errors)
		//	ai_render_sector_geometry_errors();

		//if (g_ai_render_link_specific != NONE)
		//	ai_debug_render_link_specific();

		//if (g_ai_render_links)
		//	ai_debug_render_links();

		//if (g_ai_render_user_hints)
		//	ai_render_user_hints();

		//if (g_ai_render_hints)
		//	ai_render_hints();

		//if (g_ai_render_object_hints_all)
		//	ai_render_object_hints(0);
		//else if (g_ai_render_object_hints)
		//	ai_render_object_hints(1);

		//if (g_ai_render_object_properties)
		//	ai_render_object_properties();

		//if (g_ai_render_sector_bsps)
		//	sector_bsps_debug();
		//else if (g_ai_render_giant_sector_bsps)
		//	giant_sector_bsps_debug();

		//if (g_ai_render_sector_link_errors)
		//	ai_debug_render_sector_link_errors();

		//if (g_ai_render_intersection_links)
		//	ai_debug_render_intersection_links();

		//if (g_ai_render_non_walkable_sectors)
		//	ai_debug_render_non_walkable_sectors();

		//if (g_ai_render_threshold_links)
		//	ai_debug_render_threshold_links();

		if (g_ai_render_objectives || g_ai_render_strength)
			ai_debug_render_squads();

		if (g_ai_render_suppress_combat)
			ai_debug_render_suppress_combat();

		//if (g_ai_render_ai_iterator != NONE)
		//	ai_debug_render_ai_iterator();

		//if (g_ai_render_vehicle_reservations)
		//	ai_debug_render_vehicle_reservations();

		//if (g_ai_debug_tracking_data)
		//	ai_debug_tracking_data();

		if (g_ai_debug_perception_data)
			ai_debug_perception_data();

		if (g_ai_debug_combat_status)
			debug_combat_status();

		//if (g_ai_render_tracked_props_all)
		//	ai_debug_render_tracked_props_all();

		//if (g_ai_render_targets_all)
		//	ai_debug_render_targets_all();

		//if (g_ai_render_joint_behaviors)
		//	debug_render_joint_behaviors();

		//if (g_ai_render_flocks)
		//	debug_render_flocks();

		if (g_ai_render_command_scripts)
			render_command_scripts();
	
		if (g_ai_render_dialogue_variants)
			render_dialogue_variants();
	
		//if (g_ai_render_dynamic_firing_positions)
		//	ai_debug_render_dynamic_firing_positions();

		//if (!ai_hide_actor_errors)
		//	debug_render_actor_errors();

		if (g_ai_render_vehicle_interest)
			debug_render_vehicle_interest();

		if (g_ai_render_player_battle_vector)
			debug_render_player_battle_vector();

		if (g_ai_render_player_needs_vehicle)
			debug_render_player_needs_vehicle();

		//if (g_ai_render_mission_critical)
		//	debug_render_mission_critical_ai();
	}
	
	//if (g_dialogue_debug)
	//	ai_dialogue_render_records();
}

void ai_debug_drawstack_setup(real_point3d const* position)
{
	e_output_user_index user_index = player_mapping_first_active_output_user();
	s_observer_result const* camera = observer_try_and_get_camera(user_index);

	global_ai_debug_drawstack_last_position = *position;
	global_ai_debug_drawstack_next_position = global_ai_debug_drawstack_last_position;

	if (camera)
	{
		vector3d vector{};
		vector_from_points3d(&global_ai_debug_drawstack_last_position, &camera->focus_point, &vector);
		global_ai_debug_drawstack_height = magnitude3d(&vector) / 40.0f;
	}
	else
	{
		global_ai_debug_drawstack_height = 0.05f;
	}
}

real_point3d* ai_debug_drawstack()
{
	global_ai_debug_drawstack_last_position = global_ai_debug_drawstack_next_position;
	point_from_line3d(&global_ai_debug_drawstack_last_position, global_up3d, global_ai_debug_drawstack_height, &global_ai_debug_drawstack_next_position);

	return &global_ai_debug_drawstack_last_position;
}

real_point3d* ai_debug_drawstack_offset(real offset)
{
	global_ai_debug_drawstack_last_position = global_ai_debug_drawstack_next_position;
	global_ai_debug_drawstack_next_position.z += offset;

	return &global_ai_debug_drawstack_last_position;
}

void ai_debug_string(char const* string, short tab_stop_count, short const* tab_stops, real_argb_color const* color)
{
	c_rasterizer_draw_string draw_string;
	c_font_cache_mt_safe font_cache;

	short_rectangle2d bounds{};
	bounds.x0 = 0;
	bounds.y0 = global_ai_debug_string_position;
	bounds.x1 = SHRT_MAX;
	bounds.y1 = SHRT_MAX;

	if (!color)
		color = global_real_argb_white;

	interface_set_bitmap_text_draw_mode(&draw_string, 0, -1, 0, 0, 5, 0);

	draw_string.set_color(color);
	draw_string.set_tab_stops(tab_stops, tab_stop_count);
	draw_string.set_bounds(&bounds);
	draw_string.draw(&font_cache, string);

	int16_point2d cursor{};
	draw_string.get_cursor(&cursor);
	global_ai_debug_string_position -= cursor.y - bounds.y0;
}

void render_command_scripts_helper(actor_datum* actor, long command_script_index)
{
	// #TODO: implement me

	// #TODO: `hs_thread_get`, `cs_atom_string`

	//TLS_DATA_GET_VALUE_REFERENCE(command_script_data);
	//
	//command_script_datum* command_script = (command_script_datum*)datum_get(*command_script_data, command_script_index);
	//
	//if (command_script->next_cs != NONE)
	//	render_command_scripts_helper(actor, command_script->next_cs);
	//
	//if (command_script->thread_index != NONE)
	//{
	//	hs_thread* thread = hs_thread_get(command_script->thread_index);
	//	hs_script* script = NULL;
	//	real_argb_color const* color = NULL;
	//
	//	if (thread->script_index != NONE)
	//		script = &global_scenario_get()->scripts[thread->script_index];
	//
	//	short atom_channel_start = actor->meta.swarm ? 1 : 3;
	//	for (short atom_channel = atom_channel_start - 1; atom_channel >= 0; atom_channel--)
	//	{
	//		if (command_script_index == actor->commands.last_script_index)
	//			color = global_real_argb_white;
	//		else
	//			color = global_real_argb_grey;
	//
	//		char string[202]{};
	//		switch (command_script->control[atom_channel].__unknown4)
	//		{
	//		case NONE:
	//			csstrnzcpy(string, "(NONE)", sizeof(string));
	//			break;
	//		case 0:
	//			csstrnzcpy(string, "(FAILED)", sizeof(string));
	//			break;
	//		case 1:
	//			csstrnzcpy(string, "(FINISHED)", sizeof(string));
	//			break;
	//		case 2:
	//			string[0] = '(';
	//			cs_atom_string(command_script_index, atom_channel, &string[1], sizeof(string) - 2);
	//			csstrnzcat(string, ")", sizeof(string));
	//			break;
	//		}
	//
	//		render_debug_string_at_point(ai_debug_drawstack(), string, color);
	//	}
	//
	//	if (script)
	//	{
	//		render_debug_string_at_point(ai_debug_drawstack(), script->name.get_string(), color);
	//	}
	//	else
	//	{
	//		c_static_string<256> string;
	//		render_debug_string_at_point(ai_debug_drawstack(),
	//			string.print("%s: Pri(%i) %s",
	//			hs_thread_format(command_script->thread_index),
	//			command_script->priority,
	//			command_script->reserve_mandatory ? "[M]" : " "), color);
	//	}
	//}
}

void render_command_scripts()
{
	//actor_iterator actor_iter{};
	//actor_iterator_new(&actor_iter, false);
	//while (actor_datum* actor = actor_iterator_next(&actor_iter))
	//{
	//	if (actor->commands.script_index != NONE)
	//	{
	//		real_point3d position{};
	//		point_from_line3d(&actor->input.position.head, global_up3d, 0.1f, &position);
	//		ai_debug_drawstack_setup(&position);
	//		render_command_scripts_helper(actor, actor->commands.script_index);
	//	}
	//}
}

void ai_debug_render_behavior_stacks_all()
{
	actor_iterator actor_iter{};
	actor_iterator_new(&actor_iter, false);
	while (actor_datum* actor = actor_iterator_next(&actor_iter))
	{
		real_point3d position{};
		point_from_line3d(&actor->input.position.head, global_up3d, 0.1f, &position);
		ai_debug_drawstack_setup(&position);

		for (short layer_index = 0; layer_index <= actor->state.leaf_layer; layer_index++)
			render_debug_string_at_point(ai_debug_drawstack(), behavior_names[actor_behavior_index_get(actor, layer_index)], global_real_argb_green);
	}
}

void ai_debug_render_character_names()
{
	actor_iterator actor_iter{};
	actor_iterator_new(&actor_iter, false);
	while (actor_datum* actor = actor_iterator_next(&actor_iter))
	{
		real_point3d position{};
		point_from_line3d(&actor->input.position.head, global_up3d, 0.1f, &position);
		ai_debug_drawstack_setup(&position);

		render_debug_string_at_point(ai_debug_drawstack(), c_string_builder("%s", tag_name_strip_path(tag_get_name(actor->meta.character_definition_index))).get_string(), global_real_argb_green);
	}
}

void ai_debug_render_squads()
{
	squad_iterator squad_iter{};
	squad_iterator_new(&squad_iter);
	while (squad_datum* squad = squad_iterator_next(&squad_iter))
	{
		s_scenario* scenario = global_scenario_get();
		s_squad_definition* squad_def = &scenario->squads[DATUM_INDEX_TO_ABSOLUTE_INDEX(squad_iter.squad_index)];
		real_point3d position = *global_origin3d;

		short scale = 0;
		{
			squad_actor_iterator squad_actor_iter{};
			squad_actor_iterator_new(&squad_actor_iter, squad_iter.squad_index, true);
			while (actor_datum* squad_actor = squad_actor_iterator_next(&squad_actor_iter))
			{
				add_vectors3d((vector3d*)&position, (vector3d*)&squad_actor->input.position.head, (vector3d*)&position);
				add_vectors3d((vector3d*)&position, (vector3d*)&squad_actor->input.position.body, (vector3d*)&position);
				scale += 2;
			}
		}

		if (scale > 0)
		{
			scale_vector3d((vector3d*)&position, 1.0f / (real)scale, (vector3d*)&position);
			ai_debug_drawstack_setup(&position);
			render_debug_sphere(true, &position, 0.3f, global_real_argb_red);

			squad_actor_iterator squad_actor_iter{};
			squad_actor_iterator_new(&squad_actor_iter, squad_iter.squad_index, true);
			while (actor_datum* squad_actor = squad_actor_iterator_next(&squad_actor_iter))
			{
				real_point3d center{};
				real radius = 0.0f;

				if (squad_actor->meta.unit_index == NONE)
					center = squad_actor->input.position.body;
				else
					object_get_bounding_sphere(squad_actor->meta.unit_index, &center, &radius);

				render_debug_line(true, &position, &center, squad_actor->meta.__unknown1E ? global_real_argb_yellow : global_real_argb_red);
			}

			if (g_ai_render_strength)
			{
				char string[128]{};
				csnzprintf(string, sizeof(string), "Strength: %f", squad->current_strength_fraction);
				render_debug_string_at_point(ai_debug_drawstack(), string, global_real_argb_aqua);
			}

			// #TODO: implement `ai_debug_render_objectives`
			//if (g_ai_render_objectives)
			//	ai_debug_render_objectives(squad_iter.squad_index, &position);

			render_debug_string_at_point(ai_debug_drawstack(), squad_def->name.get_string(), global_real_argb_red);
		}
	}
}

void ai_debug_render_suppress_combat()
{
	actor_iterator actor_iter{};
	actor_iterator_new(&actor_iter, true);
	while (actor_datum* actor = actor_iterator_next(&actor_iter))
	{
		if (actor->state.suppress_combat)
			render_debug_string_at_point(&actor->input.position.head, "COMBAT SUPPRESSED", global_real_argb_blue);
	}
}

void ai_debug_perception_data()
{
	TLS_DATA_GET_VALUE_REFERENCE(tracking_data);
	TLS_DATA_GET_VALUE_REFERENCE(prop_ref_data);
	TLS_DATA_GET_VALUE_REFERENCE(prop_data);
	TLS_DATA_GET_VALUE_REFERENCE(clump_data);

	c_rasterizer_draw_string draw_string;
	c_font_cache_mt_safe font_cache;
	char string[500]{};

	csnzprintf(string, sizeof(string), "Total clumps: %i/%i|nTotal clump props: %i/%i|n, Total prop-refs: %i/%i|nTotal tracks:%i/%i",
		clump_data->actual_count, 20,
		prop_data->actual_count, 256,
		prop_ref_data->actual_count, 1024,
		tracking_data->actual_count, 100);

	draw_string.draw(&font_cache, string);
}

void debug_combat_status()
{
	actor_iterator actor_iter{};
	actor_iterator_new(&actor_iter, true);
	while (actor_datum* actor = actor_iterator_next(&actor_iter))
	{
		real_point3d position{};
		point_from_line3d(&actor->input.position.head, global_up3d, 0.1f, &position);
		ai_debug_drawstack_setup(&position);

		render_debug_string_at_point(ai_debug_drawstack(), c_string_builder("Combat status: %i", actor->state.combat_status).get_string(), global_real_argb_green);
		render_debug_string_at_point(ai_debug_drawstack(), c_string_builder("Highest prop class: %i", actor->situation.highest_prop_class).get_string(), global_real_argb_green);
	}
}

void render_dialogue_variants()
{
	actor_iterator actor_iter{};
	actor_iterator_new(&actor_iter, false);
	while (actor_datum* actor = actor_iterator_next(&actor_iter))
	{
		if (actor->meta.unit_index != NONE)
		{
			unit_datum* unit = (unit_datum*)object_get_and_verify_type(actor->meta.unit_index, _object_mask_unit);
			s_seat_storage* seat_storage = (s_seat_storage*)object_header_block_get(actor->meta.unit_index, &unit->seat_storage);
			if (seat_storage->dialogue_definition_index != NONE)
			{
				s_dialogue_definition* dialogue_definition = (s_dialogue_definition*)tag_get(DIALOGUE_TAG, seat_storage->dialogue_definition_index);
				char const* mission_dialogue_designator_name = dialogue_definition->mission_dialogue_designator.get_string();
				render_debug_string_at_point(&actor->input.position.head, mission_dialogue_designator_name, global_real_argb_white);
			}
		}
	}
}

