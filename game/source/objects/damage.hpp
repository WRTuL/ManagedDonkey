#pragma once

#include "cseries/cseries.hpp"
#include "game/materials.hpp"
#include "objects/damage_owner.hpp"
#include "objects/damage_reporting.hpp"

struct s_damage_globals
{
	struct s_damage_acceleration
	{
		real_point3d point;
		vector3d acceleration;
		long object_index;
		short node_index;
		word_flags flags;
	};
	static_assert(sizeof(s_damage_acceleration) == 0x20);

	long damage_acceleration_count;
	c_static_array<s_damage_acceleration, 64> damage_accelerations;
	c_static_flags<64> damage_accelerations_evictable;
	bool damage_acceleration_queue_active;
};
static_assert(sizeof(s_damage_globals) == 0x810);

struct s_damage_data
{
	long damage_effect_definition_index;
	dword_flags flags;
	s_damage_owner damage_owner;
	long __unknown14;
	long __unknown18;
	byte __data1C[0x4];
	s_location location;
	byte __data22[2];
	real_point3d origin;
	real_point3d center;
	vector3d attacker_direction;
	vector3d __vector48;
	real __unknown54;
	real __unknown58;
	real damage_amount;
	real damage_aoe_size;
	real __unknown64;
	byte __data68[0x8];
	vector3d __vector70;
	long __unknown7C;
	real vitality;
	c_global_material_type material_type;
	short __unknown86;
	byte __data88[0x4];
	s_damage_reporting_info damage_reporting_info;
	byte __data90[0x4];
	long __unknown94;
};
static_assert(sizeof(s_damage_data) == 0x98);

struct object_damage_section
{
	short __unknown0;
	short __unknown2;
	byte __data4[0x8];
};
static_assert(sizeof(object_damage_section) == 0xC);

extern bool debug_damage_radius;
extern bool debug_damage_this_event;
extern bool debug_damage_verbose;
extern bool debug_player_damage;
extern bool debug_damage;
extern long global_debug_damage_object_index;

struct s_model_damage_info;

extern void render_debug_object_damage();

extern real __cdecl compute_total_damage(s_damage_data* damage_data, void* damage_effect_definition, void const* damage_definition, long object_index, bool* a5);
extern void __cdecl damage_acceleration_apply(s_damage_globals::s_damage_acceleration const* damage_acceleration);
extern void __cdecl damage_acceleration_queue_begin();
extern void __cdecl damage_acceleration_queue_end();
extern void __cdecl damage_initialize_for_new_map();
extern void __cdecl damage_update();
extern void __cdecl object_cause_damage(s_damage_data* damage_data, long object_index, short node_index, short region_index, short material_index, long predictability);
extern s_model_damage_info const* __cdecl object_get_damage_info(long object_index);

