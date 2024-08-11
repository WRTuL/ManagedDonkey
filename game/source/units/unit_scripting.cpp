#include "units/unit_scripting.hpp"

//.text:00B45B00 ; void __cdecl unit_scripting_kill(long)
//.text:00B45BB0 ; void __cdecl unit_scripting_kill_silent(long)
//.text:00BB1C00 ; 
//.text:00BB1C20 ; bool __cdecl unit_custom_animation_at_frame(long, long, long, bool, short)
//.text:00BB1CB0 ; bool __cdecl unit_custom_animation_relative_at_frame(long, long, long, long, bool, short)
//.text:00BB1D40 ; bool __cdecl unit_get_custom_animation_root_velocity(long, vector3d*)
//.text:00BB1E50 ; short __cdecl unit_get_custom_animation_scripting_ticks_remaining(long)
//.text:00BB1EB0 ; double __cdecl unit_get_custom_animation_time_remaining(long)
//.text:00BB1F00 ; bool __cdecl unit_is_playing_custom_animation(long)
//.text:00BB1F20 ; void __cdecl unit_play_random_ping(long)
//.text:00BB2140 ; void __cdecl unit_scripting_actively_controlled(long, bool)
//.text:00BB2190 ; void __cdecl unit_scripting_aim_without_turning(long, bool)
//.text:00BB21E0 ; void __cdecl unit_scripting_board_vehicle(long, long)
//.text:00BB2280 ; void __cdecl unit_scripting_can_blink(long, bool)
//.text:00BB22D0 ; void __cdecl unit_scripting_close(long)
//.text:00BB22F0 ; void __cdecl unit_scripting_doesnt_drop_items(long)
//.text:00BB2350 ; void __cdecl unit_scripting_drop_support_weapon(long)
//.text:00BB23C0 ; void __cdecl unit_scripting_enable_vision_mode(long, bool)
//.text:00BB2410 ; void __cdecl unit_scripting_enter_vehicle(long, long, long)
//.text:00BB2550 ; void __cdecl unit_scripting_exit_vehicle2(long, short)
//.text:00BB2650 ; void __cdecl unit_scripting_exit_vehicle(long)
//.text:00BB26C0 ; void __cdecl unit_scripting_force_reload(long)
//.text:00BB2720 ; bool __cdecl unit_scripting_get_enterable_by_player(long)
//.text:00BB2760 ; short __cdecl unit_scripting_get_grenade_count(long)
//.text:00BB27B0 ; double __cdecl unit_scripting_get_health(long)
//.text:00BB27C0 ; double __cdecl unit_scripting_get_shield(long)
//.text:00BB27D0 ; bool __cdecl unit_scripting_has_any_equipment(long)
//.text:00BB2800 ; bool __cdecl unit_scripting_has_equipment(long, long)
//.text:00BB2870 ; bool __cdecl unit_scripting_has_weapon(long, long)
//.text:00BB28A0 ; bool __cdecl unit_scripting_has_weapon_readied(long, long)
//.text:00BB2950 ; void __cdecl unit_scripting_impervious(long, bool)
//.text:00BB29C0 ; bool __cdecl unit_scripting_in_vehicle(long)
//.text:00BB2A60 ; bool __cdecl unit_scripting_is_emitting(long)
//.text:00BB2AB0 ; void __cdecl unit_scripting_limit_lipsync_to_mouth_only(long, bool)
//.text:00BB2B00 ; void __cdecl unit_scripting_lower_weapon(long, short)
//.text:00BB2B30 ; void __cdecl unit_scripting_magic_melee_attack()
//.text:00BB2B80 ; long __cdecl unit_scripting_object_get_turret(long, short)
//.text:00BB2C20 ; short __cdecl unit_scripting_object_get_turret_count(long)
//.text:00BB2CB0 ; void __cdecl unit_scripting_open(long)
//.text:00BB2CF0 ; void __cdecl unit_scripting_player_lock_gaze(long, long, real)
//.text:00BB2D30 ; void __cdecl unit_scripting_player_unlock_gaze(long)
//.text:00BB2D60 ; void __cdecl unit_scripting_raise_weapon(long, short)
//.text:00BB2D90 ; void __cdecl unit_scripting_set_active_camo(long, bool, real)
//.text:00BB2DD0 ; void __cdecl unit_scripting_set_animation_mode(long, long)
//.text:00BB2E10 ; void __cdecl unit_scripting_set_current_vitality(long, real, real)
//.text:00BB2F20 ; void __cdecl unit_scripting_set_emotion(long, long, real, real)
//.text:00BB2F60 ; void __cdecl unit_scripting_set_emotion_by_name(long, long, real, real)
//.text:00BB2FA0 ; void __cdecl unit_scripting_set_enterable_by_player(long, bool)
//.text:00BB3000 ; unit_set_seat_enterable_by_player?
//.text:00BB30C0 ; void __cdecl unit_scripting_set_integrated_flashlight(long, bool)
//.text:00BB3180 ; void __cdecl unit_scripting_set_maximum_vitality(long, real, real)
//.text:00BB31D0 ; void __cdecl unit_scripting_set_only_takes_damage_from_players_team_bit(long, bool)
//.text:00BB3220 ; void __cdecl unit_scripting_set_voice(long, long)
//.text:00BB3260 ; void __cdecl unit_scripting_spew_action(long)
//.text:00BB3280 ; bool __cdecl unit_scripting_start_user_animation_list(long, long, long, bool)
//.text:00BB3340 ; void __cdecl unit_scripting_stop_custom_animation(long)
//.text:00BB3360 ; void __cdecl unit_scripting_suspended(long, bool)
//.text:00BB33D0 ; long __cdecl unit_scripting_unit_driver(long)
//.text:00BB3400 ; long __cdecl unit_scripting_unit_gunner(long)
//.text:00BB3430 ; bool __cdecl unit_scripting_unit_in_vehicle_type(long, long)
//.text:00BB3490 ; long __cdecl unit_scripting_unit_riders(long)
//.text:00BB3530 ; bool __cdecl unit_scripting_vehicle_test_seat(long, long)
//.text:00BB3570 ; bool __cdecl unit_scripting_vehicle_test_seat_unit(long, long, long)
//.text:00BB3620 ; bool __cdecl unit_scripting_vehicle_test_seat_list(long, long, long)
//.text:00BB3730 ; bool __cdecl unit_start_user_animation(long, long, long, bool)
//.text:00BB3790 ; bool __cdecl unit_start_user_animation_loop(long, long, long, bool)
//.text:00BB37F0 ; bool __cdecl unit_start_user_animation_relative(long, long, long, bool, long)
//.text:00BB3850 ; bool __cdecl unit_start_user_animation_relative_loop(long, long, long, bool, long)
//.text:00BB38B0 ; void __cdecl units_scripting_set_current_vitality(long, real, real)
//.text:00BB3A00 ; void __cdecl units_scripting_set_maximum_vitality(long, real, real)
//.text:00BB3AA0 ; short __cdecl vehicle_scripting_load_magic(long, long, long)
//.text:00BB3C70 ; short __cdecl vehicle_scripting_unload(long, long)
//.text:00BB3D20 ; 

