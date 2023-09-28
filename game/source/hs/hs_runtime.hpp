#pragma once

#include "cseries/cseries.hpp"
#include "memory/data.hpp"

struct hs_stack_frame
{
	word stack_offset;
	long return_value;
	long tracking_index;

	// 0: _hs_thread_type_script
	// 1: [global initialize]
	// 2: [console command]
	// 3: script?
	// 4: script?
	char type;

	byte_flags __flagsD;
	byte_flags __flagsE;
	byte __unknownF;
	dword __unknown10;
};
static_assert(sizeof(hs_stack_frame) == 0x14);

struct hs_thread : s_datum_header
{
	short script_index;
	short previous_script_index;
	long sleep_until;
	long sleep_time;
	hs_stack_frame stack_pointer;
	byte stack_data[0x500];
};
static_assert(sizeof(hs_thread) == 0x524);

struct s_hs_runtime_globals
{
	bool initialized;
	bool require_gc;
	bool require_object_list_gc;
	bool globals_initializing;
	long executing_thread_index;
};
static_assert(sizeof(s_hs_runtime_globals) == 0x8);

struct hs_global_datum : s_datum_header
{
	word __unknown2;
	dword __unknown4;
};
static_assert(sizeof(hs_global_datum) == 0x8);

struct hs_distributed_global_data : s_datum_header
{
	byte __data[0x2A];
};
static_assert(sizeof(hs_distributed_global_data) == 0x2C);

struct hs_thread_tracking_data : s_datum_header
{
	word __unknown2;
	dword __unknown4;
	dword __unknown8;
};
static_assert(sizeof(hs_thread_tracking_data) == 0xC);

extern bool debug_trigger_volumes;

extern bool __cdecl hs_can_cast(short actual_type, short desired_type);
extern bool __cdecl hs_evaluate(long thread_index, long expression_index, long destination_pointer, long* out_cast);
extern bool __cdecl hs_object_type_can_cast(short actual_type, short desired_type);
extern long __cdecl hs_runtime_script_begin(short script_index, short script_type, char thread_type);
extern long __cdecl hs_thread_new(char thread_index, long script_index, bool deterministic);
extern void __cdecl render_debug_trigger_volumes();

