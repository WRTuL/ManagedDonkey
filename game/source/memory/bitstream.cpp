#include "memory/bitstream.hpp"

#include "cseries/console.hpp"

#include <assert.h>

void c_bitstream::append(c_bitstream const* stream)
{
	FUNCTION_BEGIN(true);

	assert(stream->m_state == _bitstream_state_write_finished);
	assert(writing());

	write_raw_data(stream->m_data, stream->m_data_size_in_bits);
	__unknown98 += stream->__unknown98;
	__unknown9C += stream->__unknown9C;

	//DECLFUNC(0x00557100, void, __thiscall, c_bitstream const*, c_bitstream const*)(this, stream);
}

void c_bitstream::begin_consistency_check()
{
	FUNCTION_BEGIN(true);

	reset(_bitstream_state_read_only_for_consistency);

	//DECLFUNC(0x00557490, void, __thiscall, c_bitstream const*)(this);
}

void c_bitstream::begin_reading()
{
	FUNCTION_BEGIN(true);

	reset(_bitstream_state_reading);

	//DECLFUNC(0x005574A0, void, __thiscall, c_bitstream const*)(this);
}

void c_bitstream::begin_writing(long data_size_alignment)
{
	FUNCTION_BEGIN(true);

	m_data_size_alignment = data_size_alignment;
	reset(_bitstream_state_writing);

	//DECLFUNC(0x005574B0, void, __thiscall, c_bitstream const*, long)(this, data_size_alignment);
}

void c_bitstream::data_is_untrusted(bool is_untrusted)
{
	FUNCTION_BEGIN(true);

	// `m_data_is_untrusted` doesn't exist in release builds
	//m_data_is_untrusted = is_untrusted;
	
	// this function is empty in release builds
	DECLFUNC(0x00557D60, void, __thiscall, c_bitstream const*, bool)(this, is_untrusted);
}

void c_bitstream::discard_remaining_data()
{
	FUNCTION_BEGIN(true);

	assert(reading());

	m_data_size_in_bits = 8 * m_data_size_bytes;
	m_window = 0;
	m_window_bits_used = 0;

	//DECLFUNC(0x00557F60, void, __thiscall, c_bitstream const*)(this);
}

bool c_bitstream::overflowed() const
{
	FUNCTION_BEGIN(true);

	return m_current_bit_position > 8 * m_data_size_bytes;
}

bool c_bitstream::error_occurred() const
{
	FUNCTION_BEGIN(true);

	bool result = overflowed();
	if (__unknown14)
		return true;
	return result;

	//DECLFUNC(0x00558090, bool, __thiscall, c_bitstream const*)(this);
}

bool c_bitstream::reading() const
{
	FUNCTION_BEGIN(true);

	return m_state == _bitstream_state_reading || m_state == _bitstream_state_read_only_for_consistency;
}

bool c_bitstream::writing() const
{
	FUNCTION_BEGIN(true);

	return m_state == _bitstream_state_writing;
}

void c_bitstream::finish_consistency_check()
{
	FUNCTION_BEGIN(true);

	finish_reading();

	//DECLFUNC(0x005580B0, void, __thiscall, c_bitstream const*)(this);
}

void c_bitstream::finish_reading()
{
	FUNCTION_BEGIN(true);

	m_state = _bitstream_state_read_finished;

	//DECLFUNC(0x005580C0, void, __thiscall, c_bitstream const*)(this);
}

void c_bitstream::finish_writing(long* bits_remaining)
{
	FUNCTION_BEGIN(true);

	DECLFUNC(0x005580D0, void, __thiscall, c_bitstream const*, long*)(this, bits_remaining);
}

long c_bitstream::get_current_bit_position()
{
	FUNCTION_BEGIN(true);

	return m_current_bit_position;

	//DECLFUNC(0x00558240, void, __thiscall, c_bitstream const*)(this);
}

byte const* c_bitstream::get_data(long* data_length) const
{
	FUNCTION_BEGIN(true);

	//return DECLFUNC(0x00558250, byte const*, __thiscall, c_bitstream const*, long*)(this, data_length);

	assert(!writing());
	assert(data_length);

	*data_length = m_data_size_bytes;
	return m_data;
}

void c_bitstream::pop_position(bool pop)
{
	FUNCTION_BEGIN(true);

	assert(reading() || writing());
	assert(m_position_stack_depth > 0);

	DECLFUNC(0x00558310, void, __thiscall, c_bitstream const*, bool)(this, pop);
}

bool c_bitstream::read_bool()
{
	FUNCTION_BEGIN(true);

	assert(reading());

	return DECLFUNC(0x00558570, bool, __thiscall, c_bitstream const*)(this);
}

void c_bitstream::read_raw_data(void* data, long size_in_bits)
{
	FUNCTION_BEGIN(true);

	assert(reading());

	DECLFUNC(0x00558740, void, __thiscall, c_bitstream const*, void*, long)(this, data, size_in_bits);
}

dword c_bitstream::read_integer(long size_in_bits)
{
	FUNCTION_BEGIN(true);

	assert(reading());
	assert(size_in_bits>0 && size_in_bits<=LONG_BITS);

	//dword value = read_value_internal(size_in_bits)
	//assert(value < (1 << size_in_bits));

	return DECLFUNC(0x005589A0, dword, __thiscall, c_bitstream const*, long)(this, size_in_bits);
}

void c_bitstream::read_point3d(char const* name, long_point3d* point, long axis_encoding_size_in_bits)
{
	FUNCTION_BEGIN(true);

	assert(reading());
	assert(axis_encoding_size_in_bits>=0&&axis_encoding_size_in_bits<=SIZEOF_BITS(point->n[0]));

	//for (long axis = 0; axis < 3; ++axis)
	//{
	//	point->n[axis] = read_value_internal(axis_encoding_size_in_bits);
	//	assert(point->n[axis] < (1 << axis_encoding_size_in_bits));
	//}

	DECLFUNC(0x00558C50, void, __thiscall, c_bitstream const*, char const*, long_point3d*, long)(this, name, point, axis_encoding_size_in_bits);
}

real c_bitstream::read_quantized_real(char const* name, real min_value, real max_value, long size_in_bits, bool exact_midpoint, bool exact_endpoints)
{
	FUNCTION_BEGIN(true);

	assert(reading());

	return DECLFUNC(0x00559080, real, __thiscall, c_bitstream const*, char const*, real, real, long, bool, bool)(this, name, min_value, max_value, size_in_bits, exact_midpoint, exact_endpoints);
}

void c_bitstream::read_secure_address(char const* name, s_transport_secure_address* address)
{
	FUNCTION_BEGIN(true);

	assert(reading());
	assert(address);

	DECLFUNC(0x00559360, void, __thiscall, c_bitstream const*, char const*, s_transport_secure_address*)(this, name, address);
}

void c_bitstream::read_string(char const* name, char* _string, long max_string_size)
{
	FUNCTION_BEGIN(true);

	assert(reading());
	assert(_string);
	assert(max_string_size>0);

	DECLFUNC(0x00559380, void, __thiscall, c_bitstream const*, char const*, char*, long)(this, name, _string, max_string_size);
}

void c_bitstream::read_string_utf8(char const* name, char* char_string, long max_string_size)
{
	FUNCTION_BEGIN(true);

	assert(reading());
	assert(char_string);
	assert(max_string_size>0);

	DECLFUNC(0x00559670, void, __thiscall, c_bitstream const*, char const*, utf8*, long)(this, name, char_string, max_string_size);
}

void c_bitstream::read_string_wchar(char const* name, wchar_t* _string, long max_string_size)
{
	FUNCTION_BEGIN(true);

	assert(reading());
	assert(_string);
	assert(max_string_size>0);

	DECLFUNC(0x00559880, void, __thiscall, c_bitstream const*, char const*, wchar_t*, long)(this, name, _string, max_string_size);
}

void c_bitstream::read_vector(char const* name, real_vector3d* vector, real min_value, real max_value, long step_count_size_in_bits, long size_in_bits)
{
	FUNCTION_BEGIN(true);

	DECLFUNC(0x00559AB0, void, __thiscall, c_bitstream const*, char const*, real_vector3d*, real, real, long, long)(this, name, vector, min_value, max_value, step_count_size_in_bits, size_in_bits);
}

void c_bitstream::reset(long state)
{
	FUNCTION_BEGIN(true);

	assert(state>=0 && state<k_bitstream_state_count);
	DECLFUNC(0x00559BE0, void, __thiscall, c_bitstream const*, long)(this, state);
}

void c_bitstream::set_data(byte* data, long data_length)
{
	FUNCTION_BEGIN(true);

	m_data = data;
	m_data_max = &data[data_length];
	m_data_size_bytes = data_length;
	reset(_bitstream_state_initial);

	//DECLFUNC(0x00559D90, void, __thiscall, c_bitstream const*, byte*, long)(this, data, data_length);
}

bool c_bitstream::would_overflow(long size_in_bits) const
{
	FUNCTION_BEGIN(true);

	return DECLFUNC(0x00559E90, bool, __thiscall, c_bitstream const*, long)(this, size_in_bits);
}

void c_bitstream::write_raw_data(void const* data, long size_in_bits)
{
	FUNCTION_BEGIN(true);

	DECLFUNC(0x0055A000, void, __thiscall, c_bitstream const*, void const*, long)(this, data, size_in_bits);
}

void c_bitstream::write_point3d(char const* name, long_point3d const* point, long axis_encoding_size_in_bits)
{
	FUNCTION_BEGIN(true);

	DECLFUNC(0x0055A1E0, void, __thiscall, c_bitstream const*, long_point3d const*, long)(this, point, axis_encoding_size_in_bits);
}

void c_bitstream::write_quantized_real(char const* name, real* value, real min_value, real max_value, long size_in_bits, bool exact_midpoint, bool exact_endpoints)
{
	FUNCTION_BEGIN(true);

	assert(writing());

	DECLFUNC(0x0055A2B0, void, __thiscall, c_bitstream const*, char const*, real*, real, real, long, bool, bool)(this, name, value, min_value, max_value, size_in_bits, exact_midpoint, exact_endpoints);
}

void c_bitstream::write_secure_address(char const* name, s_transport_secure_address const* address)
{
	FUNCTION_BEGIN(true);

	assert(writing());
	assert(address);

	DECLFUNC(0x0055A410, void, __thiscall, c_bitstream const*, char const*, s_transport_secure_address const*)(this, name, address);
}

void c_bitstream::write_string(char const* name, char const* _string, long max_string_size)
{
	FUNCTION_BEGIN(true);

	assert(writing());
	assert(_string);
	assert(max_string_size>0);
	//assert(strnlen(_string, max_string_size) < max_string_size);

	DECLFUNC(0x0055A430, void, __thiscall, c_bitstream const*, char const*, char const*, long)(this, name, _string, max_string_size);
}

void c_bitstream::write_string_utf8(char const* name, utf8 const* char_string, long max_string_size)
{
	FUNCTION_BEGIN(true);

	assert(writing());
	assert(char_string);
	assert(max_string_size>0);
	//assert(strnlen(char_string, max_string_size) < max_string_size);

	DECLFUNC(0x0055A650, void, __thiscall, c_bitstream const*, char const*, utf8 const*, long)(this, name, char_string, max_string_size);
}

void c_bitstream::write_string_wchar(char const* name, wchar_t const* _string, long max_string_size)
{
	FUNCTION_BEGIN(true);

	assert(writing());
	assert(_string);
	assert(max_string_size>0);

	DECLFUNC(0x0055A6D0, void, __thiscall, c_bitstream const*, char const*, wchar_t const*, long)(this, name, _string, max_string_size);
}