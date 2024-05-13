#pragma once

#include "cseries/cseries.hpp"

extern real_point3d global_ai_debug_drawstack_next_position;
extern real global_ai_debug_drawstack_height;
extern real_point3d global_ai_debug_drawstack_last_position;
extern short global_ai_debug_string_position;
extern bool g_ai_render;
extern bool g_ai_render_firing_positions_all;
extern bool g_ai_render_lineoffire;
extern bool g_ai_render_lineofsight;
extern bool g_ai_render_ballistic_lineoffire;
extern long g_ai_debug_selected_actor_unit_index;
extern long g_ai_debug_selected_actor_index;
extern bool g_ai_debug_path;
extern bool g_ai_render_paths_failed;
extern bool g_ai_render_aiming_validity;
extern bool g_ai_render_all_actors;
extern bool g_ai_render_dialogue;
extern bool g_ai_render_dialogue_queue;
extern bool g_ai_render_dialogue_player_weights;
extern bool g_ai_render_speech;
extern bool g_ai_print_speech;
extern bool g_ai_render_spatial_effects;
extern bool g_ai_render_clumps;
extern bool g_ai_render_clump_props;
extern bool g_ai_render_clump_props_all;
extern bool g_ai_render_decisions;
extern bool g_ai_render_decisions_all;
extern bool g_ai_render_behavior_stack_all;
extern bool g_ai_render_character_names;
extern bool g_ai_render_stimuli;
extern bool g_ai_render_sectors;
extern long g_ai_render_sectors_range_max;
extern long g_ai_render_sectors_range_min;
extern bool g_ai_render_sector_geometry_errors;
extern long g_ai_render_link_specific;
extern bool g_ai_render_links;
extern bool g_ai_render_user_hints;
extern bool g_ai_render_hints;
extern bool g_ai_render_object_hints_all;
extern bool g_ai_render_object_hints;
extern bool g_ai_render_object_properties;
extern bool g_ai_render_sector_bsps;
extern bool g_ai_render_giant_sector_bsps;
extern bool g_ai_render_sector_link_errors;
extern bool g_ai_render_intersection_links;
extern bool g_ai_render_non_walkable_sectors;
extern bool g_ai_render_threshold_links;
extern bool g_ai_render_orders;
extern bool g_ai_render_suppress_combat;
extern bool g_ai_render_vehicle_reservations;
extern bool g_ai_render_objectives;
extern bool g_ai_render_strength;
extern bool g_ai_debug_tracking_data;
extern bool g_ai_debug_perception_data;
extern bool g_ai_debug_combat_status;
extern bool g_ai_render_tracked_props_all;
extern bool g_ai_render_targets_all;
extern bool g_ai_render_joint_behaviors;
extern bool g_ai_render_flocks;
extern bool g_ai_render_command_scripts;
extern bool g_ai_render_dialogue_variants;
extern bool g_ai_render_dynamic_firing_positions;
extern bool g_ai_render_vehicle_interest;
extern bool g_ai_render_player_battle_vector;
extern bool g_ai_render_player_needs_vehicle;
extern bool g_ai_render_mission_critical;

extern void __cdecl ai_debug_render();

extern void ai_debug_drawstack_setup(real_point3d const* position);
extern real_point3d* ai_debug_drawstack();
extern real_point3d* ai_debug_drawstack_offset(real offset);
extern void ai_debug_string(char const* string, short tab_stop_count, short const* tab_stops, real_argb_color const* color);

extern void ai_debug_render_behavior_stacks_all();
extern void ai_debug_render_character_names();
extern void ai_debug_render_sectors();
extern void ai_render_object_properties();
extern void render_command_scripts();
extern void ai_debug_render_intersection_links();
extern void ai_debug_render_threshold_links();
extern void ai_debug_render_squads();
extern void ai_debug_render_suppress_combat();
extern void ai_debug_render_vehicle_reservations();
extern void ai_debug_tracking_data();
extern void ai_debug_perception_data();
extern void debug_combat_status();
extern void ai_debug_render_tracked_props_all();
extern void ai_debug_render_targets_all();
extern void render_dialogue_variants();
extern void ai_debug_render_dynamic_firing_positions();

