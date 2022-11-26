#pragma once

#include <stdio.h>

class c_console
{
public:
    static void initialize(char const* window_title);
    static void dispose();

    static void write(char const* format, ...);
    static void write_line(char const* format, ...);
    static void write(wchar_t const* format, ...);
    static void write_line(wchar_t const* format, ...);

    static void write(char const* format, va_list list);
    static void write_line(char const* format, va_list list);
    static void write(wchar_t const* format, va_list list);
    static void write_line(wchar_t const* format, va_list list);

protected:
    static FILE* m_file;
};

#ifdef _DEBUG
#define FUNCTION_BEGIN(PRINT) { if (PRINT) { c_console::write_line(__FUNCTION__); c_console::write_line("%s %d\n", __FILE__, __LINE__); } }
#else
#define FUNCTION_BEGIN(...)
#endif // _DEBUG

void get_error_message(unsigned long message_id, char(&message_buffer)[2048]);