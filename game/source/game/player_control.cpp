#include "game/player_control.hpp"

#include "cseries/console.hpp"
#include "game/game.hpp"
#include "memory/thread_local.hpp"

inline s_player_control_globals* player_control_globals_get()
{
	FUNCTION_BEGIN(true);

	s_thread_local_storage* tls = get_tls();
	if (!tls || !tls->player_control_globals)
		return nullptr;

	return tls->player_control_globals;
}

inline bool player_control_get_machinima_camera_enabled()
{
	FUNCTION_BEGIN(true);

	if (game_in_progress() && !game_is_ui_shell())
		return player_control_globals_get()->machinima_camera_enabled;

	return false;
}

inline bool player_control_get_machinima_camera_use_old_controls()
{
	FUNCTION_BEGIN(true);

	if (player_control_get_machinima_camera_enabled())
		return player_control_globals_get()->machinima_camera_use_old_controls;

	return false;
}

inline bool player_control_get_machinima_camera_debug()
{
	FUNCTION_BEGIN(true);

	if (player_control_get_machinima_camera_enabled())
		return player_control_globals_get()->machinima_camera_debug;

	return false;
}

inline void player_control_set_machinima_camera(bool enabled, bool debug, bool use_old_controls)
{
	FUNCTION_BEGIN(true);

	s_player_control_globals* player_control_globals = player_control_globals_get();
	if (!player_control_globals)
		return;

	player_control_globals->machinima_camera_enabled = enabled;
	player_control_globals->machinima_camera_debug = debug;
	player_control_globals->machinima_camera_use_old_controls = use_old_controls;
}

inline void player_control_toggle_machinima_camera_enabled()
{
	FUNCTION_BEGIN(true);

	s_player_control_globals* player_control_globals = player_control_globals_get();
	if (!player_control_globals)
		return;

	player_control_globals->machinima_camera_enabled = !player_control_globals->machinima_camera_enabled;
}

inline void player_control_toggle_machinima_camera_use_old_controls()
{
	FUNCTION_BEGIN(true);

	s_player_control_globals* player_control_globals = player_control_globals_get();
	if (!player_control_globals)
		return;

	player_control_globals->machinima_camera_use_old_controls = !player_control_globals->machinima_camera_use_old_controls;
}

inline void player_control_toggle_machinima_camera_debug()
{
	FUNCTION_BEGIN(true);

	s_player_control_globals* player_control_globals = player_control_globals_get();
	if (!player_control_globals)
		return;

	player_control_globals->machinima_camera_debug = !player_control_globals->machinima_camera_debug;
}

inline void player_control_toggle_player_input(long user_index)
{
	FUNCTION_BEGIN(true);

	s_player_control_globals* player_control_globals = player_control_globals_get();
	if (!player_control_globals)
		return;

	player_control_globals->input_user_states[user_index].player_input_locked = !player_control_globals->input_user_states[user_index].player_input_locked;
}