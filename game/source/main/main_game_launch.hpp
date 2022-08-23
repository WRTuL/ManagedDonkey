#pragma once

#include "game/game_options.hpp"

struct s_main_game_launch_globals
{
	// main_game_change_immediate
	// main_game_load_from_core_name
	char core_name[256];

	// main_game_launch
	// main_game_launch_set_coop_player_count
	// main_game_launch_set_multiplayer_splitscreen_count
	long player_count;

	game_options& options;
};

extern s_main_game_launch_globals g_launch_globals;

//extern void main_game_launch_default();
//extern void main_game_launch_default_editor();
//extern void main_game_launch_initialize();
extern void main_game_launch_set_map_name(char const* map_name);
extern void main_game_launch_set_difficulty(e_campaign_difficulty_level campaign_difficulty);
extern void main_game_launch_campaign();
extern void main_game_launch_survival();
extern void main_game_launch_multiplayer();
extern void main_game_launch_ui_shell();
extern void main_game_launch_set_coop_player_count(long);
extern void main_game_launch_set_multiplayer_splitscreen_count(long);
extern void main_game_launch_set_multiplayer_engine(char const* engine_name);
//extern void main_game_launch_set_multiplayer_variant(char const*);
//extern void main_game_launch_set_initial_zone_set_index(long);
//extern void main_game_launch_set_insertion_point(short);
//extern void main_game_launch_set_tick_rate(long);
//extern void main_game_launch_legacy(char const*);
extern void main_game_launch(const char* map_name);
//extern void main_game_launch_process();
extern void main_game_launch_set_active_skulls_primary(long primary_skulls);
extern void main_game_launch_set_active_skulls_secondary(long secondary_skulls);