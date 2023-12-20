#include "cseries/cseries_windows_debug_pc.hpp"

#include "config/version.hpp"
#include "editor/editor_stubs.hpp"
#include "main/main.hpp"
#include "memory/module.hpp"
#include "multithreading/synchronization.hpp"
#include "multithreading/synchronized_value.hpp"
#include "multithreading/threads.hpp"
#include "rasterizer/rasterizer.hpp"
#include "tag_files/files.hpp"
#include "tag_files/files_windows.hpp"
#include "tag_files/tag_groups.hpp"

#include <windows.h>
#include <dbghelp.h>
#include <float.h>
#include <Psapi.h>

struct s_exception_type_info
{
	char const* exception_string;
	dword exception_parameters[3];
};
static_assert(sizeof(s_exception_type_info) == 0x10);

struct s_exception_information
{
	c_synchronized_long exception_occurred;
	long thread_id;
	CONTEXT context_record;
	dword exception_code;
	dword exception_flags;
	void* exception_address;
	dword number_parameters;
	s_exception_type_info exception_type_info;
};
static_assert(sizeof(s_exception_information) == 0x2F4);

REFERENCE_DECLARE(0x0238E878, bool, g_set_always_a_debugger_present);
REFERENCE_DECLARE(0x0238E879, bool, g_set_never_a_debugger_present);
REFERENCE_DECLARE(0x0238E87C, dword, g_exception_time);
REFERENCE_DECLARE(0x0238E880, PEXCEPTION_POINTERS, g_exception_pointers);
REFERENCE_DECLARE(0x0238E884, c_synchronized_long, g_exception_caching_in_progress);
REFERENCE_DECLARE(0x0238E888, s_exception_information, g_exception_information);

HOOK_DECLARE(0x0051C020, exceptions_update);

char const* GetExceptionString(dword code)
{
	switch (code)
	{
	case EXCEPTION_DATATYPE_MISALIGNMENT:    return "EXCEPTION_DATATYPE_MISALIGNMENT";
	case EXCEPTION_BREAKPOINT:               return "EXCEPTION_BREAKPOINT";
	case EXCEPTION_SINGLE_STEP:              return "EXCEPTION_SINGLE_STEP";
	case EXCEPTION_ACCESS_VIOLATION:         return "EXCEPTION_ACCESS_VIOLATION";
	case EXCEPTION_NONCONTINUABLE_EXCEPTION: return "EXCEPTION_NONCONTINUABLE_EXCEPTION";
	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:    return "EXCEPTION_ARRAY_BOUNDS_EXCEEDED";
	case EXCEPTION_FLT_DENORMAL_OPERAND:     return "EXCEPTION_FLT_DENORMAL_OPERAND";
	case EXCEPTION_FLT_DIVIDE_BY_ZERO:       return "EXCEPTION_FLT_DIVIDE_BY_ZERO";
	case EXCEPTION_FLT_INEXACT_RESULT:       return "EXCEPTION_FLT_INEXACT_RESULT";
	case EXCEPTION_FLT_INVALID_OPERATION:    return "EXCEPTION_FLT_INVALID_OPERATION";
	case EXCEPTION_FLT_OVERFLOW:             return "EXCEPTION_FLT_OVERFLOW";
	case EXCEPTION_FLT_STACK_CHECK:          return "EXCEPTION_FLT_STACK_CHECK";
	case EXCEPTION_FLT_UNDERFLOW:            return "EXCEPTION_FLT_UNDERFLOW";
	case EXCEPTION_INT_DIVIDE_BY_ZERO:       return "EXCEPTION_INT_DIVIDE_BY_ZERO";
	case EXCEPTION_INT_OVERFLOW:             return "EXCEPTION_INT_OVERFLOW";
	case EXCEPTION_PRIV_INSTRUCTION:         return "EXCEPTION_PRIV_INSTRUCTION";
	case EXCEPTION_ILLEGAL_INSTRUCTION:      return "EXCEPTION_ILLEGAL_INSTRUCTION";
	case STATUS_FLOAT_MULTIPLE_FAULTS:       return "STATUS_FLOAT_MULTIPLE_FAULTS";
	case STATUS_FLOAT_MULTIPLE_TRAPS:        return "STATUS_FLOAT_MULTIPLE_TRAPS";
	case 0xC06D007E:                         return "VCPPEXCEPTION_MODULE_NOT_FOUND";
	case 0xC06D007F:                         return "VCPPEXCEPTION_PROC_NOT_FOUND";
	}

	return nullptr;
}

char const* GetExceptionFlagsString(DWORD exception)
{
	switch (exception)
	{
	case EXCEPTION_NONCONTINUABLE:           return "EXCEPTION_NONCONTINUABLE";
	case EXCEPTION_UNWINDING:                return "EXCEPTION_UNWINDING";
	case EXCEPTION_EXIT_UNWIND:              return "EXCEPTION_EXIT_UNWIND";
	case EXCEPTION_STACK_INVALID:            return "EXCEPTION_STACK_INVALID";
	case EXCEPTION_NESTED_CALL:              return "EXCEPTION_NESTED_CALL";
	case EXCEPTION_TARGET_UNWIND:            return "EXCEPTION_TARGET_UNWIND";
	case EXCEPTION_COLLIDED_UNWIND:          return "EXCEPTION_COLLIDED_UNWIND";
	case EXCEPTION_SOFTWARE_ORIGINATE:       return "EXCEPTION_SOFTWARE_ORIGINATE";
	case EXCEPTION_ACCESS_VIOLATION:         return "EXCEPTION_ACCESS_VIOLATION";
	}

	return "";
}

void exception_print_recursive(PEXCEPTION_RECORD exception_record, s_file_reference file)
{
	if (!exception_record)
		return;

	file_printf(&file, "ExceptionAddress: 0x%08X\n", (dword)exception_record->ExceptionAddress);
	file_printf(&file, "   ExceptionCode: 0x%08X\n", (dword)exception_record->ExceptionCode);
	file_printf(&file, "  ExceptionFlags: 0x%08X, %s\n", (dword)exception_record->ExceptionFlags, GetExceptionFlagsString(exception_record->ExceptionFlags));

	for (DWORD i = 0; i < exception_record->NumberParameters; i++)
		file_printf(&file, "\tExceptionInformation[%i]: 0x%08X\n", i, (dword)exception_record->ExceptionInformation[i]);

	file_printf(&file, "\n");

	exception_print_recursive(exception_record->ExceptionRecord, file);
}

void __cdecl build_exception_information(_EXCEPTION_POINTERS* exception_pointers, s_exception_information* exception_information)
{
	//INVOKE(0x0051BC10, build_exception_information, exception_pointers, exception_information);

	if (exception_information)
	{
		csmemset(exception_information, 0, sizeof(s_exception_information));
		if (exception_pointers)
		{
			exception_information->thread_id = GetCurrentThreadId();
			csmemcpy(&exception_information->context_record, exception_pointers->ContextRecord, sizeof(exception_information->context_record));
			exception_information->exception_code = exception_pointers->ExceptionRecord->ExceptionCode;
			exception_information->exception_flags = exception_pointers->ExceptionRecord->ExceptionFlags;
			exception_information->exception_address = exception_pointers->ExceptionRecord->ExceptionAddress;
			if (exception_pointers->ExceptionRecord != (PEXCEPTION_RECORD)-0x14)
			{
				exception_information->number_parameters = min(4, exception_pointers->ExceptionRecord->NumberParameters);
				csmemcpy(&exception_information->exception_type_info, exception_pointers->ExceptionRecord->ExceptionInformation, 4 * exception_information->number_parameters);
			}
			exception_information->exception_occurred = 1;
		}
	}
}

void __cdecl cache_exception_information(_EXCEPTION_POINTERS* exception_pointers)
{
	//INVOKE(0x0051BCC0, cache_exception_information, exception_pointers);

	if (!g_exception_caching_in_progress.set(1) && !has_cached_exception())
	{
		build_exception_information(exception_pointers, &g_exception_information);
		g_exception_information.exception_occurred = 1;
		g_exception_time = system_milliseconds();
	}
}

long __cdecl exceptions_update()
{
	//INVOKE(0x0051C020, exceptions_update);

	if (!has_cached_exception())
		return 0;

	main_loop_pregame_disable(true);

	dword code = g_exception_information.exception_code;
	char const* exception_code_string = GetExceptionString(g_exception_information.exception_code);
	if (!g_catch_exceptions)
	{
		g_exception_information.exception_occurred = 0;
		main_loop_pregame_disable(false);
		return 0;
	}

	if (code == 'stk')
	{
		if (version_is_tracked_build() || g_force_upload_even_if_untracked)
		{
			rasterizer_dump_display_to_bmp("crash_report\\crash_screenshot.bmp");
			release_locks_safe_for_crash_release();
		}

		g_exception_information.exception_occurred = 0;
		main_loop_pregame_disable(false);
		return -1;
	}

	c_static_string<1156> crash_info;
	char const* thread_name = get_thread_name_from_thread_id(g_exception_information.thread_id);
	long thread_id = g_exception_information.thread_id;

	_clearfp();
	//event_logs_flush();
	release_locks_safe_for_crash_release();

	generate_event(_event_level_message, "crash: ");
	generate_event(_event_level_message, "crash: FATAL ERROR ENCOUNTERED");
	generate_event(_event_level_message, "crash: ");
	generate_event(_event_level_message, "crash: ");

	dword exception_address = address_from_pointer(g_exception_information.exception_address);
	char const* symbol_name = symbol_name_from_address(exception_address, nullptr);
	generate_event(_event_level_message, "crash: %s",
		version_get_full_string());

	crash_info.print("version:\r\n%s\r\n",
		version_get_full_string());

	generate_event(_event_level_message, "crash:   thread information: thread_name: %s thread_id: %08lx",
		thread_name,
		thread_id);
	crash_info.append_print("thread information:\r\n thread_name: %s, thread_id: %08lx\r\n",
		thread_name,
		thread_id);

	if (code == 'asrt' && g_exception_information.number_parameters >= 4)
	{
		char const* exception_string = g_exception_information.exception_type_info.exception_string;
		char const* parameter0 = (char const*)g_exception_information.exception_type_info.exception_parameters[0];
		dword parameter1 = g_exception_information.exception_type_info.exception_parameters[1];
		bool parameter2 = !!g_exception_information.exception_type_info.exception_parameters[2];

		generate_event(_event_level_message, "crash: %s at %s,#%d",
			parameter2 ? "### ASSERTION FAILED: " : "### RUNTIME WARNING: ",
			parameter0,
			parameter1);

		crash_info.append_print("halt:\r\n%s at %s,#%d\r\n",
			parameter2 ? "### ASSERTION FAILED: " : "### RUNTIME WARNING: ",
			parameter0,
			parameter1);

		if (exception_string)
		{
			generate_event(_event_level_message, "crash:   %s",
				exception_string);
			crash_info.append_print("halt information:\r\n  %s\r\n",
				exception_string);
		}
	}
	else
	{
		if (exception_code_string)
		{
			generate_event(_event_level_message, "crash: ### RUNTIME ERROR: %s at %08lX",
				exception_code_string,
				exception_address);
			generate_event(_event_level_message, "crash:   (%s)",
				symbol_name);

			crash_info.append_print("halt:\r\n### RUNTIME ERROR: %s at %08lX\r\n",
				exception_code_string,
				exception_address);
			crash_info.append_print("halt information:\r\n  (%s)\r\n",
				symbol_name);
		}
		else
		{
			generate_event(_event_level_message, "crash: ### RUNTIME ERROR: UNKNOWN EXCEPTION %08lX at %08lX",
				exception_code_string,
				exception_address);
			generate_event(_event_level_message, "crash:   (%s)",
				symbol_name);

			crash_info.append_print("halt:\r\n### RUNTIME ERROR: UNKNOWN EXCEPTION %08lX at %08lX\r\n",
				code,
				exception_address);
			crash_info.append_print("halt information:\r\n  (%s)\r\n",
				symbol_name);
		}

		if (code == EXCEPTION_ACCESS_VIOLATION)
		{
			if (g_exception_information.number_parameters >= 2)
			{
				generate_event(_event_level_message, "crash:   tried to %s address %08lx",
					g_exception_information.exception_type_info.exception_string ? "write" : "read",
					g_exception_information.exception_type_info.exception_parameters[0]);

				crash_info.append_print("crash:   tried to %s address %08lx\r\n",
					g_exception_information.exception_type_info.exception_string ? "write" : "read",
					g_exception_information.exception_type_info.exception_parameters[0]);
			}
		}
		else if (code == 0xC06D007E && g_exception_information.number_parameters) // VCPPEXCEPTION_MODULE_NOT_FOUND
		{
			generate_event(_event_level_message, "crash:   tried to load %s",
				*((char const**)g_exception_information.exception_type_info.exception_string + 3));
			crash_info.append_print("  tried to load %s\r\n",
				*((char const**)g_exception_information.exception_type_info.exception_string + 3));
		}
	}

	main_write_stack_to_crash_info_status_file(crash_info.get_string(), &g_exception_information.context_record);
	editor_save_progress();
	//call_fatal_error_callbacks();
	if (version_is_tracked_build() || g_force_upload_even_if_untracked)
	{
		rasterizer_dump_display_to_bmp("crash_report\\crash_screenshot.bmp");
		release_locks_safe_for_crash_release();
	}

	if (is_debugger_present())
		__debugbreak();
	else
		main_halt_and_catch_fire();

	long result = !is_debugger_present() ? 1 : -1;

	g_exception_information.exception_occurred = 0;
	main_loop_pregame_disable(false);

	return result;
}

void __cdecl force_debugger_always_present(bool debugger_always_present)
{
	//INVOKE(0x0051C1E0, force_debugger_always_present, debugger_always_present);

	g_set_always_a_debugger_present = debugger_always_present;
	if (debugger_always_present)
		g_set_never_a_debugger_present = false;
}

void __cdecl force_debugger_not_present(bool debugger_not_present)
{
	//INVOKE(0x0051C210, force_debugger_not_present, debugger_not_present);

	g_set_never_a_debugger_present = debugger_not_present;
	if (debugger_not_present)
		g_set_always_a_debugger_present = false;
}

bool __cdecl is_debugger_present()
{
	if (g_set_always_a_debugger_present)
		return true;

	if (g_set_never_a_debugger_present)
		return false;

	return IsDebuggerPresent();
}

bool __cdecl has_cached_exception()
{
	//INVOKE(0x0051C300, has_cached_exception);

	return g_exception_information.exception_occurred.peek() != 0;
}

