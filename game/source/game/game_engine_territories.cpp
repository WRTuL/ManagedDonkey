#include "game/game_engine_territories.hpp"

#include "memory/byte_swapping.hpp"

REFERENCE_DECLARE(0x050D9F80, c_game_engine_territories_variant*, territories_variant);

void c_game_engine_territories_variant::byteswap()
{
	static_cast<c_game_engine_base_variant*>(this)->byteswap();

	bswap_word_inplace(m_variant_flags);
	bswap_word_inplace(m_respawn_on_capture);
	bswap_word_inplace(m_capture_time);
	bswap_word_inplace(m_sudden_death_time);
	m_defender_traits.byteswap();
	m_attacker_traits.byteswap();
}

