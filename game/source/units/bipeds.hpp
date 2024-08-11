#pragma once

#include "ai/sector.hpp"
#include "cseries/cseries.hpp"
#include "memory/ring_buffer.hpp"
#include "physics/character_physics.hpp"
#include "units/units.hpp"

struct _biped_datum
{
	word_flags flags;

	short pathfinding_structure_index;
	long pathfinding_time;
	long pathfinding_surface_index;
	c_sector_ref pathfinding_sector;
	long pathfinding__unknown10;
	long pathfinding_object_index;
	dword pathfinding_bsp_reference;
	real_point3d pathfinding_point;

	byte __data28[0x18];

	long current_bump_object_index;
	long bump_object_index;
	char bump_ticks;
	char jump_control_ticks;
	byte stun_ticks; // char?
	char last_known_speed_scale;
	real lean;
	real camera_offset_z;
	real camera_offset_y;
	real camera_height;
	long jump_time;
	long land_time;
	short current_gate_type;
	short current_gate_index;
	long current_gate_start_time;

	byte __data6C[0x28];

	c_character_physics_component physics;
	object_header_block_reference simulation_interpolation;
	object_header_block_reference last_node_matrices_storage;
	vector3d root_offset;
	vector3d ground_fit_normal;
	real pivot_on_foot_scale;
	real pivot_on_foot_scale_boost;
	real_point3d pivot_point;
	vector2d pivot_fixup;

	real_matrix4x3 __matrix150;
	real_matrix4x3 __matrix184;

	byte __data1B8[0xC];

	t_static_ring_buffer<real_matrix4x3, 3> root_matrix_history;
	real landing_recovery_offset;
	real pendulum_scale;
	vector3d pendulum_vector;
	real gravity_scale;

	// linked, armor related
	long  customized_area_object_indices[10];
	short customized_area_indices[10];

	// linked
	long __unknown2C0;
	short __unknown2C4;
	byte __data2C6[0x1];
	bool __unknown2C7;
};
static_assert(sizeof(_biped_datum) == 0x2C8);

struct biped_datum
{
	long definition_index;
	_object_datum object;
	_motor_datum motor;
	_unit_datum unit;
	_biped_datum biped;
};
static_assert(sizeof(biped_datum) == sizeof(long) + sizeof(_object_datum) + sizeof(_motor_datum) + sizeof(_unit_datum) + sizeof(_biped_datum));

extern bool debug_objects_physics_control_node;
extern bool debug_objects_biped_autoaim_pills;
extern bool debug_objects_ground_plane;
extern bool debug_objects_movement_mode;
extern bool debug_biped_throttle;
extern bool debug_objects_unit_pathfinding_surface;
extern bool debug_objects_pendulum;

extern void __cdecl biped_bumped_object(long biped_index, long object_index, vector3d const* old_velocity);
extern void __cdecl biped_get_autoaim_pill(long biped_index, real_point3d* base, vector3d* height, real* autoaim_width);
extern void __cdecl biped_get_physics_pill(long biped_index, real_point3d* position, real* height, real* radius);
extern void __cdecl biped_get_sentinel_animation_node_position_and_velocity(long biped_index, real_point3d* position, vector3d* velocity);
extern void __cdecl biped_get_sight_position(long biped_index, short estimate_mode, bool offset_camera, real_point3d const* estimated_body_position, vector3d const* a5, vector3d const* desired_facing_vector, vector3d const* desired_gun_offset, real_point3d* camera_position);
extern void __cdecl biped_scripting_ragdoll(long biped_index);
extern void __cdecl biped_render_debug(long biped_index);

