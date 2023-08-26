#include "physics/collision_references.hpp"

#include "physics/bsp3d.hpp"
#include "structures/structure_bsp_definitions.hpp"

c_collision_edge_reference::c_collision_edge_reference() :
	c_collision_bsp_reference(),
	m_edge_index(0)
{
}

c_collision_edge_reference::c_collision_edge_reference(c_collision_bsp_reference bsp_reference, long index) :
	c_collision_bsp_reference(bsp_reference),
	m_edge_index(index)
{
}

long c_collision_edge_reference::get_edge_index() const
{
	return m_edge_index;
}

long c_collision_edge_reference::get_vertex_index(long index) const
{
	if (is_small())
		return m_bsp->edges[m_edge_index].vertex_indices[index];

	return m_large_bsp->edges[m_edge_index].vertex_indices[index];
}

long c_collision_edge_reference::get_edge_index(long index) const
{
	if (is_small())
		return m_bsp->edges[m_edge_index].edge_indices[index];

	return m_large_bsp->edges[m_edge_index].edge_indices[index];
}

long c_collision_edge_reference::get_surface_index(long index) const
{
	if (is_small())
		return m_bsp->edges[m_edge_index].surface_indices[index];

	return m_large_bsp->edges[m_edge_index].surface_indices[index];
}

c_collision_vertex_reference::c_collision_vertex_reference() :
	c_collision_bsp_reference(),
	m_vertex_index(0)
{
}

c_collision_vertex_reference::c_collision_vertex_reference(c_collision_bsp_reference bsp_reference, long index) :
	c_collision_bsp_reference(bsp_reference),
	m_vertex_index(index)
{
}

long c_collision_vertex_reference::get_vertex_index() const
{
	return m_vertex_index;
}

real_point3d* c_collision_vertex_reference::get_position() const
{
	if (is_small())
		return &m_bsp->vertices[m_vertex_index].point;

	return &m_large_bsp->vertices[m_vertex_index].point;
}

long c_collision_vertex_reference::get_first_edge_index() const
{
	if (is_small())
		return m_bsp->vertices[m_vertex_index].first_edge;

	return m_large_bsp->vertices[m_vertex_index].first_edge;
}

long c_collision_vertex_reference::get_sink() const
{
	if (is_small())
		return m_bsp->vertices[m_vertex_index].sink;

	return m_large_bsp->vertices[m_vertex_index].sink;
}

c_collision_surface_reference::c_collision_surface_reference() :
	c_collision_bsp_reference(),
	m_surface_index(0)
{
}

c_collision_surface_reference::c_collision_surface_reference(c_collision_bsp_reference bsp_reference, long index) :
	c_collision_bsp_reference(bsp_reference),
	m_surface_index(index)
{
}

byte_flags c_collision_surface_reference::get_flags() const
{
	if (is_small())
		return m_bsp->surfaces[m_surface_index].flags;

	return m_large_bsp->surfaces[m_surface_index].flags;
}

plane3d const* c_collision_surface_reference::get_plane(plane3d* plane) const
{
	ASSERT(plane);

	if (is_small())
		return bsp3d_get_plane_from_designator_internal(m_bsp, m_bsp->surfaces[m_surface_index].plane, plane);

	return bsp3d_get_plane_from_designator_internal(m_large_bsp, m_large_bsp->surfaces[m_surface_index].plane, plane);
}

