#pragma once

enum e_chud_message_context
{
	_chud_message_context_self = 0,
	_chud_message_context_friendly,
	_chud_message_context_enemy,
	_chud_message_context_neutral,

	k_chud_message_context_count
};

struct c_chud_messaging_manager
{
	enum e_chud_state_text_placement
	{
		_chud_state_text_placement_right = 0,
		_chud_state_text_placement_left,
		_chud_state_text_placement_bottom,
		_chud_state_text_placement_bottom_primary,
		_chud_state_text_placement_unknown4,
		_chud_state_text_placement_unknown5,

		k_chud_state_text_placement_count
	};

	// #TODO: map this whole ass struct
};

extern void __cdecl chud_messaging_post(long user_index, wchar_t const* message_text, e_chud_message_context chud_message_context);
extern void __cdecl chud_messaging_special_autosave(bool end);
extern void __cdecl chud_messaging_special_load(bool end);
extern void __cdecl chud_messaging_special_saving(bool end);
extern void __cdecl chud_post_action_response(long user_index);
extern bool __cdecl chud_set_state_text(long user_index, long message, long a3, c_chud_messaging_manager::e_chud_state_text_placement text_placement);

