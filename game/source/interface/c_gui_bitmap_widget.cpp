#include "interface/c_gui_bitmap_widget.hpp"

void __cdecl c_gui_bitmap_widget::set_sprite_frame(long sprite_frame)
{
	m_sprite_frame = sprite_frame;
}

void __cdecl c_gui_bitmap_widget::set_sprite_sequence(long sprite_sequence)
{
	m_sprite_sequence = sprite_sequence;
}

bitmap_data const* __cdecl c_gui_bitmap_widget::get_current_bitmap() const
{
	return INVOKE_CLASS_MEMBER2(__vftable->__funcs[38], c_gui_bitmap_widget::get_current_bitmap);
}

