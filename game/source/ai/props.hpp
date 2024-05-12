#pragma once

#include "cseries/cseries.hpp"
#include "memory/data.hpp"

struct prop_ref_datum :
	s_datum_header
{
	char type;
	char dialogue_event;
	char dialogue_index;
	byte dialogue_ticks;
	char stimulus;
	byte stimulus_decay_ticks;
	long actor_index;
	long prop_index;
	long object_index;
	long tracking_index;

	byte __data18[0x4];

	char acknowledgement;
	char perception;

	byte __data1E[0x1];

	byte_flags flags;

	byte __data20[0x4];

	long actor_next_prop_ref_index;
	long actor_prev_prop_ref_index;
	long clump_next_prop_ref_index;
	long clump_prev_prop_ref_index;

	real distance;
	real salience;
};
static_assert(sizeof(prop_ref_datum) == 0x3C);

struct prop_datum :
	s_datum_header
{
	byte __data[0xC2];
};
static_assert(sizeof(prop_datum) == 0xC4);

struct tracking_datum :
	s_datum_header
{
	byte __data[0xFE];
};
static_assert(sizeof(tracking_datum) == 0x100);

