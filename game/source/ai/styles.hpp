#pragma once

#include "cseries/cseries.hpp"
#include "tag_files/tag_groups.hpp"

enum e_combat_status
{
	_combat_status_latch_at_idle = 0,
	_combat_status_latch_at_alert,
	_combat_status_latch_at_combat,

	k_combat_status_count
};

enum e_style_attitude
{
	_style_attitude_normal = 0,
	_style_attitude_timid,
	_style_attitude_aggressive,

	k_style_attitude_count
};

enum e_style_control_flags
{
	_style_control_flag_new_behaviors_default_to_on_bit = 0,

	k_style_control_flags
};

enum e_behavior
{
	_behavior_GENERAL,
	_behavior_GENERAL_root,
	_behavior_GENERAL_null,
	_behavior_GENERAL_null_discrete,
	_behavior_GENERAL_obey,
	_behavior_GENERAL_guard,
	_behavior_GENERAL_follow_behavior,
	_behavior_GENERAL_ready,
	_behavior_GENERAL_smash_obstacle,
	_behavior_GENERAL_destroy_obstacle,
	_behavior_GENERAL_perch,
	_behavior_GENERAL_cover_friend,
	_behavior_GENERAL_blind_panic,
	_behavior_GENERAL_combat,
	_behavior_GENERAL_squad_patrol_behavior,

	_behavior_BROKEN,
	_behavior_BROKEN_broken_behavior,
	_behavior_BROKEN_huddle_impulse,
	_behavior_BROKEN_huddle_behavior,
	_behavior_BROKEN_kamikaze_behavior,
	_behavior_BROKEN_kamikaze_impulse,
	_behavior_BROKEN_berserk_impulse,
	_behavior_BROKEN_flee_impulse,
	_behavior_BROKEN_scatter_impulse,

	_behavior_ENGAGE,
	_behavior_ENGAGE_equipment,
	_behavior_ENGAGE_engage,
	_behavior_ENGAGE_fight,
	_behavior_ENGAGE_fight_positioning,
	_behavior_ENGAGE_melee_charge,
	_behavior_ENGAGE_melee_leaping_charge,
	_behavior_ENGAGE_surpris,
	_behavior_ENGAGE_grenade_impulse,
	_behavior_ENGAGE_anti_vehicle_grenade,
	_behavior_ENGAGE_stalk,
	_behavior_ENGAGE_flank,
	_behavior_ENGAGE_berserk_wander_impulse,
	_behavior_ENGAGE_stalker_camo_control,
	_behavior_ENGAGE_leader_abandoned_berserk,
	_behavior_ENGAGE_unassailable_grenade_impulse,
	_behavior_ENGAGE_perimeter,
	_behavior_ENGAGE_perimeter_timeout_morph,
	_behavior_ENGAGE_perimeter_infection_spew,

	_behavior_BERSERK,
	_behavior_BERSERK_shield_depleted_berserk,
	_behavior_BERSERK_last_man_berserk,
	_behavior_BERSERK_stuck_with_grenade_berserk,

	_behavior_PRESEARCH,
	_behavior_PRESEARCH_presearch,
	_behavior_PRESEARCH_presearch_uncover,
	_behavior_PRESEARCH_destroy_cover,
	_behavior_PRESEARCH_suppressing_fire,
	_behavior_PRESEARCH_grenade_uncover,
	_behavior_PRESEARCH_leap_on_cover,

	_behavior_LEADER,
	_behavior_LEADER_search_sync,
	_behavior_LEADER_engage_sync,

	_behavior_SEARCH,
	_behavior_SEARCH_search,
	_behavior_SEARCH_uncover,
	_behavior_SEARCH_investigate,
	_behavior_SEARCH_pursuit_sync,
	_behavior_SEARCH_pursuit,
	_behavior_SEARCH_refresh_target,
	_behavior_SEARCH_sense_target,
	_behavior_SEARCH_postsearch,
	_behavior_SEARCH_coverme_investigate,

	_behavior_SELF_DEFENSE,
	_behavior_SELF_DEFENSE_self_preservation,
	_behavior_SELF_DEFENSE_cover,
	_behavior_SELF_DEFENSE_cover_peek,
	_behavior_SELF_DEFENSE_avoid,
	_behavior_SELF_DEFENSE_evasion_impulse,
	_behavior_SELF_DEFENSE_dive_impulse,
	_behavior_SELF_DEFENSE_danger_cover_impulse,
	_behavior_SELF_DEFENSE_danger_crouch_impulse,
	_behavior_SELF_DEFENSE_proximity_melee,
	_behavior_SELF_DEFENSE_proximity_self_preservation,
	_behavior_SELF_DEFENSE_unreachable_enemy_cover,
	_behavior_SELF_DEFENSE_unassailable_enemy_cover,
	_behavior_SELF_DEFENSE_scary_target_cover,
	_behavior_SELF_DEFENSE_group_emerge,
	_behavior_SELF_DEFENSE_shield_depleted_cover,
	_behavior_SELF_DEFENSE_kungfu_cover,

	_behavior_RETREAT,
	_behavior_RETREAT_retreat,
	_behavior_RETREAT_retreat_grenade,
	_behavior_RETREAT_flee,
	_behavior_RETREAT_cower,
	_behavior_RETREAT_low_shield_retreat,
	_behavior_RETREAT_scary_target_retreat,
	_behavior_RETREAT_leader_dead_retreat,
	_behavior_RETREAT_peer_dead_retreat,
	_behavior_RETREAT_danger_retreat,
	_behavior_RETREAT_proximity_retreat,
	_behavior_RETREAT_charge_when_cornered,
	_behavior_RETREAT_surprise_retreat,
	_behavior_RETREAT_overheated_weapon_retreat,

	_behavior_AMBUSH,
	_behavior_AMBUSH_ambush,
	_behavior_AMBUSH_coordinated_ambush,
	_behavior_AMBUSH_proximity_ambush,
	_behavior_AMBUSH_vulnerable_enemy_ambush,
	_behavior_AMBUSH_nowhere_to_run_ambush,

	_behavior_VEHICLE,
	_behavior_VEHICLE_enter_vehicle,
	_behavior_VEHICLE_enter_friendly_vehicle,
	_behavior_VEHICLE_vehicle_enter_impulse,
	_behavior_VEHICLE_vehicle_entry_engage_impulse,
	_behavior_VEHICLE_vehicle_board,
	_behavior_VEHICLE_vehicle_fight,
	_behavior_VEHICLE_vehicle_fight_boost,
	_behavior_VEHICLE_vehicle_charge,
	_behavior_VEHICLE_vehicle_ram_behavior,
	_behavior_VEHICLE_vehicle_cover,
	_behavior_VEHICLE_damage_vehicle_cover,
	_behavior_VEHICLE_exposed_rear_cover_impulse,
	_behavior_VEHICLE_player_endagered_cover_impulse,
	_behavior_VEHICLE_vehicle_avoid,
	_behavior_VEHICLE_vehicle_pickup,
	_behavior_VEHICLE_vehicle_player_pickup,
	_behavior_VEHICLE_vehicle_exit_impulse,
	_behavior_VEHICLE_danger_vehicle_exit_impulse,
	_behavior_VEHICLE_vehicle_flip_impulse,
	_behavior_VEHICLE_vehicle_flip,
	_behavior_VEHICLE_vehicle_turtle,
	_behavior_VEHICLE_vehicle_engage_patrol_impulse,
	_behavior_VEHICLE_vehicle_engage_wander_impulse,

	_behavior_POSTCOMBAT,
	_behavior_POSTCOMBAT_postcombat,
	_behavior_POSTCOMBAT_post_postcombat,
	_behavior_POSTCOMBAT_check_friend,
	_behavior_POSTCOMBAT_shoot_corpse,
	_behavior_POSTCOMBAT_postcombat_approach,

	_behavior_ALERT,
	_behavior_ALERT_alert,

	_behavior_IDLE,
	_behavior_IDLE_idle,
	_behavior_IDLE_inspect,
	_behavior_IDLE_wander_behavior,
	_behavior_IDLE_flight_wander,
	_behavior_IDLE_patrol,
	_behavior_IDLE_fall_sleep,

	_behavior_BUGGERS,
	_behavior_BUGGERS_bugger_ground_uncover,

	_behavior_SWARMS,
	_behavior_SWARMS_swarm_root,
	_behavior_SWARMS_swarm_attack,
	_behavior_SWARMS_support_attack,
	_behavior_SWARMS_infect,
	_behavior_SWARMS_scatter,

	_behavior_COMBATFORMS,
	_behavior_COMBATFORMS_combat_form_berserk_control,
	_behavior_COMBATFORMS_eject_parasite,

	_behavior_SENTINELS,
	_behavior_SENTINELS_enforcer_weapon_control,
	_behavior_SENTINELS_grapple,

	_behavior_ENGINEER,
	_behavior_ENGINEER_engineer_control,
	_behavior_ENGINEER_engineer_control_slave,
	_behavior_ENGINEER_engineer_control_free,
	_behavior_ENGINEER_engineer_control_equipment,
	_behavior_ENGINEER_engineer_explode,
	_behavior_ENGINEER_engineer_broken_detonation,
	_behavior_ENGINEER_boost_allies,

	_behavior_GUARDIANS,
	_behavior_GUARDIANS_guardian_surge,
	_behavior_GUARDIANS_guardian_proximity_surge,
	_behavior_GUARDIANS_guardian_danger_surge,
	_behavior_GUARDIANS_guardian_isolation_surge,

	_behavior_PUREFORMS,
	_behavior_PUREFORMS_group_morph_impulse,
	_behavior_PUREFORMS_arrival_morph_impulse,
	_behavior_PUREFORMS_pureform_default_impulse,
	_behavior_PUREFORMS_search_morph,
	_behavior_PUREFORMS_stealth_active_camo_control,
	_behavior_PUREFORMS_stealth_damage_morph,
	_behavior_PUREFORMS_stealth_stalk,
	_behavior_PUREFORMS_stealth_stalk_thwarted,
	_behavior_PUREFORMS_stealth_stalk_group,
	_behavior_PUREFORMS_stealth_charge_recover,
	_behavior_PUREFORMS_ranged_proximity_morph,
	_behavior_PUREFORMS_tank_distance_damage_morph,
	_behavior_PUREFORMS_tank_throttle_control,
	_behavior_PUREFORMS_stealth_morph,
	_behavior_PUREFORMS_tank_morph,
	_behavior_PUREFORMS_ranged_morph,
	_behavior_PUREFORMS_ranged_turtle,
	_behavior_PUREFORMS_ranged_uncover,

	_behavior_SCARAB,
	_behavior_SCARAB_scarab_root,
	_behavior_SCARAB_scarab_cure_isolation,
	_behavior_SCARAB_scarab_combat,
	_behavior_SCARAB_scarab_fight,
	_behavior_SCARAB_scarab_target_lock,
	_behavior_SCARAB_scarab_search,
	_behavior_SCARAB_scarab_search_pause,

	_behavior_ATOMS,
	_behavior_ATOMS_go_to,

	_behavior_ACTIVITIES,
	_behavior_ACTIVITIES_activity,
	_behavior_ACTIVITIES_posture,
	_behavior_ACTIVITIES_activity_default,

	_behavior_SPECIAL,
	_behavior_SPECIAL_formation,
	_behavior_SPECIAL_grunt_scared_by_elite,
	_behavior_SPECIAL_stunned,
	_behavior_SPECIAL_cure_isolation,
	_behavior_SPECIAL_deploy_turret,

	k_behavior_count
};

struct special_movement_definition;
struct style_behavior_name;
struct style_palette_entry
{
	c_static_string<32> name;

	// Combat status decay options
	// 
	// Controls how combat status is allowed to be automatically reduced in the absence of combat stimuli.
	// 'Latch at X' means that once the level of x is attained (and/or surpassed) the combat status never falls below it.
	// Not applicable when style is applied to a character tag.
	c_enum<e_combat_status, short, _combat_status_latch_at_idle, k_combat_status_count> combat_status_decay_options;

	// Atittude
	// 
	// Indicates general stance for style.
	// This tells us which of the property blocks in the character definition to reference (e.g. timid defense properties).
	// Not applicable when style is applied to a character tag.
	c_enum<e_style_attitude, short, _style_attitude_normal, k_style_attitude_count> atittude;

	// Style Behavior Control
	// 
	// Check the appropriate box to turn on/off the given behavior
	c_flags<e_style_control_flags, dword, k_style_control_flags> style_control;

	c_static_flags<k_behavior_count> behaviors;

	c_typed_tag_block<special_movement_definition> special_movement;
	c_typed_tag_block<style_behavior_name> behavior_list;
};
static_assert(sizeof(style_palette_entry) == 0x5C);

enum e_special_movement_flags
{
	_special_movement_flag_jump_bit = 0,
	_special_movement_flag_climb_bit,
	_special_movement_flag_vault_bit,
	_special_movement_flag_mount_bit,
	_special_movement_flag_hoist_bit,
	_special_movement_flag_wall_jump_bit,
	_special_movement_flag_na_bit,
	_special_movement_flag_rail_bit,
	_special_movement_flag_seam_bit,
	_special_movement_flag_door_bit,

	k_special_movement_flags
};

struct special_movement_definition
{
	c_flags<e_special_movement_flags, dword, k_special_movement_flags> special_movement1;
};
static_assert(sizeof(special_movement_definition) == sizeof(dword));

struct style_behavior_name
{
	c_static_string<32> behavior_name;
};
static_assert(sizeof(style_behavior_name) == sizeof(c_static_string<32>));

extern long __cdecl style_get_by_name(char const* name);

