#include "scenario/scenario.hpp"

#include "cache/cache_files.hpp"
#include "cseries/console.hpp"
#include "cseries/cseries.hpp"
#include "hf2p/hf2p.hpp"
#include "main/levels.hpp"
#include "memory/module.hpp"
#include "scenario/scenario_definitions.hpp"
#include "scenario/scenario_tags_fixup.hpp"
#include "tag_files/tag_groups.hpp"

#include <assert.h>

HOOK_DECLARE(0x004EA5E0, scenario_load);

long& global_scenario_index = *reinterpret_cast<long*>(0x0189CCF8);

scenario*& global_scenario = *reinterpret_cast<scenario**>(0x022AAEB4);

scenario* global_scenario_get()
{
	FUNCTION_BEGIN(true);

	// halo online
	return tag_get<scenario>('scnr', global_scenario_index);

	// halo 3
	//assert(global_scenario);
	//return global_scenario;
}

//bool scenario_tags_match(enum e_campaign_id, enum e_map_id, char const*)
bool __cdecl scenario_tags_match(long campaign_id, long map_id, char const* scenario_path)
{
	FUNCTION_BEGIN(true);

	//return INVOKE(0x004EB820, scenario_tags_match, campaign_id, map_id, scenario_path);

	assert(scenario_path != 0);

	scenario* scenario = global_scenario_get();
	if (levels_map_id_is_fake(map_id) || (campaign_id == -1 && map_id == -1))
		return true;

	if (scenario->campaign_id == campaign_id && scenario->map_id == map_id)
		return true;

	return false;
}

void __cdecl scenario_invalidate()
{
	FUNCTION_BEGIN(true);

	return INVOKE(0x004EA3E0, scenario_invalidate);
}

void on_scenario_loaded();

//bool __cdecl scenario_load(enum e_campaign_id, enum e_map_id, char const*)
bool __cdecl scenario_load(long campaign_id, long map_id, char const* scenario_path)
{
	FUNCTION_BEGIN(true);

	//bool result = false;
	//HOOK_INVOKE(result =, scenario_load, campaign_id, map_id, scenario_path);
	//return result;

	// saber function, crashes in `hf2p_game_client_cache_release.exe!sub_A28EC0` if not called
	hf2p_scenario_load();

	if (scenario_tags_load(scenario_path))
	{
		if (scenario_tags_match(campaign_id, map_id, scenario_path))
		{
			scenario_tags_fixup();
			scenario_tags_load_finished();
			hf2p_scenario_tags_load_finished();

			on_scenario_loaded();
			return true;
		}
		else
		{
			scenario_tags_unload();
			scenario_invalidate();

			return false;
		}
	}

	tag_load_missing_tags_report();
	return false;
}

#define PRINT_ZONE_SETS()\
if (scenario->zone_sets.count)\
{\
	c_console::write_line("zone sets");\
	for (long i = 0; i < scenario->zone_sets.count; i++)\
	{\
		s_scenario_zone_set* zone_set = scenario->zone_sets.elements + i;\
		assert(zone_set);\
		char const* name = zone_set->name.get_string();\
		if (*name)\
			c_console::write_line("    %s", name);\
	}\
	c_console::write_line("");\
}

#define PRINT_CAMPAIN_PLAYERS()\
if (scenario->campaign_players.count)\
{\
	c_console::write_line("campaign players");\
	for (long i = 0; i < scenario->campaign_players.count; i++)\
	{\
		scenario_campaign_player_representation_names_block* campaign_player = scenario->campaign_players.elements + i;\
		assert(campaign_player);\
		char const* name = campaign_player->name.get_string();\
		if (*name)\
			c_console::write_line("    %s", name);\
	}\
	c_console::write_line("");\
}

#define PRINT_OBJECT_NAMES()\
if (scenario->object_names.count)\
{\
	c_console::write_line("object names");\
	for (long i = 0; i < scenario->object_names.count; i++)\
	{\
		scenario_object_name* object_name = scenario->object_names.elements + i;\
		assert(object_name);\
		char const* name = object_name->name;\
		if (*name)\
			c_console::write_line("    %s", name);\
	}\
	c_console::write_line("");\
}

#define PRINT_MAP_VARIANT_PALETTES(NAME)\
if (scenario->map_variant_##NAME##_palette.count)\
{\
	c_console::write_line("%s palette", #NAME);\
	for (long i = 0; i < scenario->map_variant_##NAME##_palette.count; i++)\
	{\
		scenario_object_palette_entry_with_string_id* palette = scenario->map_variant_##NAME##_palette.elements + i;\
		assert(palette);\
		char const* display_name = palette->display_name.get_string();\
		if (*display_name)\
			c_console::write_line("    %s", display_name);\
	}\
	c_console::write_line("");\
}

#define PRINT_SOFT_CEILINGS()\
if (scenario->soft_ceilings.count)\
{\
	c_console::write_line("soft ceilings");\
	for (long i = 0; i < scenario->soft_ceilings.count; i++)\
	{\
		s_scenario_soft_ceiling* soft_ceiling = scenario->soft_ceilings.elements + i;\
		assert(soft_ceiling);\
		char const* name = soft_ceiling->name.get_string();\
		if (name)\
			c_console::write_line("    %s", name);\
	}\
	c_console::write_line("");\
}

#define PRINT_PLAYER_STARTING_PROFILES()\
if (scenario->player_starting_profile.count)\
{\
	c_console::write_line("player starting profile");\
	for (long i = 0; i < scenario->player_starting_profile.count; i++)\
	{\
		scenario_starting_profile* profile = scenario->player_starting_profile.elements + i;\
		assert(profile);\
		char const* name = profile->name;\
		if (*name)\
			c_console::write_line("    %s", name);\
	}\
	c_console::write_line("");\
}
void on_scenario_loaded()
{
	scenario* scenario = global_scenario_get();

	PRINT_ZONE_SETS();
	PRINT_CAMPAIN_PLAYERS();
	PRINT_OBJECT_NAMES();
	PRINT_MAP_VARIANT_PALETTES(vehicle);
	PRINT_MAP_VARIANT_PALETTES(weapon);
	PRINT_MAP_VARIANT_PALETTES(equipment);
	PRINT_MAP_VARIANT_PALETTES(scenery);
	PRINT_MAP_VARIANT_PALETTES(teleporters);
	PRINT_MAP_VARIANT_PALETTES(goals);
	PRINT_MAP_VARIANT_PALETTES(spawners);
	PRINT_SOFT_CEILINGS();
	PRINT_PLAYER_STARTING_PROFILES();

	printf("");
}

#undef PRINT_MAP_VARIANT_PALETTES
#undef PRINT_ZONE_SETS