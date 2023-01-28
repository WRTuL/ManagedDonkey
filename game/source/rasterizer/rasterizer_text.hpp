#pragma once

struct IDirect3DTexture9;
struct bitmap_data_block_def;
struct c_rasterizer_texture_ref
{
public:
	static void __cdecl allocate(c_rasterizer_texture_ref& texture_ref, long width, long height, long levels, unsigned long format, long a6, bool a7, long a8, long a9);
	IDirect3DTexture9* __cdecl get_d3d_texture() const;
	static void __cdecl release(c_rasterizer_texture_ref& texture_ref);

	bool __cdecl valid();

protected:
	unsigned short m_datum_ref;
	unsigned short __unknown2;
};
static_assert(sizeof(c_rasterizer_texture_ref) == 0x4);

