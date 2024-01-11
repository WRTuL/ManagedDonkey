#include "memory/thread_local.hpp"

#include "cache/restricted_memory_regions.hpp"
#include "memory/module.hpp"

#include <windows.h>

/* k_game_state_update_region  */ REFERENCE_DECLARE(0x01861570, t_restricted_allocation_manager, g_simulation_gamestate_entity_data_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x0189D094, t_restricted_allocation_manager, g_main_gamestate_timing_data_allocator);
/* k_game_state_render_region  */ REFERENCE_DECLARE(0x0189D0A0, t_restricted_allocation_manager, g_main_render_timing_data_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x0189D248, t_restricted_allocation_manager, g_main_time_globals_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x0189D838, t_restricted_allocation_manager, g_deterministic_random_seed_ptr_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x0189DFA0, t_restricted_allocation_manager, g_game_globals_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x0189E0E0, t_restricted_allocation_manager, g_player_data_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x0189E0EC, t_restricted_allocation_manager, g_players_globals_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x0189ED8C, t_restricted_allocation_manager, g_local_game_engine_globals_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x0189ED98, t_restricted_allocation_manager, g_game_engine_globals_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x0189F8C8, t_restricted_allocation_manager, g_game_time_globals_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x0189F9F0, t_restricted_allocation_manager, g_breakable_surface_globals_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x0189F9FC, t_restricted_allocation_manager, g_breakable_surface_set_broken_event_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x018A0D1C, t_restricted_allocation_manager, g_player_mapping_globals_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x018A0F30, t_restricted_allocation_manager, g_director_globals_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x018A0F3C, t_restricted_allocation_manager, g_director_camera_scripted_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x018A1218, t_restricted_allocation_manager, g_hs_thread_deterministic_data_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x018A1224, t_restricted_allocation_manager, g_hs_thread_tracking_data_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x018A1230, t_restricted_allocation_manager, g_hs_thread_non_deterministic_data_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x018A123C, t_restricted_allocation_manager, g_hs_global_data_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x018A1248, t_restricted_allocation_manager, g_hs_distributed_global_data_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x018A1254, t_restricted_allocation_manager, g_hs_runtime_globals_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x018A1D84, t_restricted_allocation_manager, g_effect_data_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x018A1D90, t_restricted_allocation_manager, g_event_data_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x018A1D9C, t_restricted_allocation_manager, g_effect_location_data_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x018A1DA8, t_restricted_allocation_manager, g_effect_lightprobe_slot_data_allocator);
/* k_game_state_render_region  */ REFERENCE_DECLARE(0x018A1DB4, t_restricted_allocation_manager, g_effect_lightprobe_data_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x018A1DC0, t_restricted_allocation_manager, g_effect_counts_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x018A1DCC, t_restricted_allocation_manager, g_effect_message_queue_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x018A2364, t_restricted_allocation_manager, g_havok_game_state_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x018B4A08, t_restricted_allocation_manager, g_player_control_globals_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x018B4A14, t_restricted_allocation_manager, g_player_control_globals_deterministic_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x018B4B64, t_restricted_allocation_manager, g_game_looping_sound_data_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x018B4B70, t_restricted_allocation_manager, g_game_sound_globals_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x018B4B7C, t_restricted_allocation_manager, g_game_sound_scripted_impulses_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x018B5084, t_restricted_allocation_manager, g_structure_seam_globals_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x018B54A8, t_restricted_allocation_manager, g_active_portal_bitvectors_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x018BAEAC, t_restricted_allocation_manager, g_campaign_metagame_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x018BB1D8, t_restricted_allocation_manager, g_observer_globals_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x018BB1E4, t_restricted_allocation_manager, g_observer_gamestate_globals_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x018BB318, t_restricted_allocation_manager, g_rumble_globals_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x018BB3E8, t_restricted_allocation_manager, g_bink_globals_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x018BE248, t_restricted_allocation_manager, g_sound_class_data_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x018BE8D4, t_restricted_allocation_manager, g_game_allegiance_globals_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x018BEA20, t_restricted_allocation_manager, g_atmosphere_fog_globals_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x018BEAD4, t_restricted_allocation_manager, g_scenario_soft_ceilings_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x018BEBA8, t_restricted_allocation_manager, g_player_effects_globals_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x018BEFA8, t_restricted_allocation_manager, g_havok_proxy_data_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x018BF0B4, t_restricted_allocation_manager, g_cinematic_globals_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x018BF0C0, t_restricted_allocation_manager, g_cinematic_new_globals_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x018BF0CC, t_restricted_allocation_manager, g_cinematic_light_globals_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x018BF328, t_restricted_allocation_manager, g_physics_constants_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x018BF3F4, t_restricted_allocation_manager, g_animation_threads_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x018BF4AC, t_restricted_allocation_manager, g_game_save_globals_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x018BF568, t_restricted_allocation_manager, g_screen_effect_data_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x018BF628, t_restricted_allocation_manager, g_player_effect_globals_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x018E91D0, t_restricted_allocation_manager, g_scenario_interpolator_globals_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x018E9288, t_restricted_allocation_manager, g_survival_mode_globals_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x018E933C, t_restricted_allocation_manager, g_player_training_globals_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x018E93E8, t_restricted_allocation_manager, g_scenario_kill_trigger_volumes_state_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x018E94D0, t_restricted_allocation_manager, g_future_development_allocator);
/* k_global_render_data_region */ REFERENCE_DECLARE(0x018E95A0, t_restricted_allocation_manager, g_decal_counts_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x018E9614, t_restricted_allocation_manager, g_decal_message_queue_allocator);
/* k_global_render_data_region */ REFERENCE_DECLARE(0x018E9620, t_restricted_allocation_manager, g_decal_system_allocator);
/* k_global_render_data_region */ REFERENCE_DECLARE(0x018E962C, t_restricted_allocation_manager, g_decal_array_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x018E99F4, t_restricted_allocation_manager, g_impact_data_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x018E9A00, t_restricted_allocation_manager, g_impact_array_data_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x018E9A0C, t_restricted_allocation_manager, g_impact_globals_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x018EB658, t_restricted_allocation_manager, g_object_list_header_data_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x018EB664, t_restricted_allocation_manager, g_object_list_data_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x018ED1D8, t_restricted_allocation_manager, g_camera_script_globals_allocator);
/* k_game_state_render_region  */ REFERENCE_DECLARE(0x018F2E78, t_restricted_allocation_manager, g_particles_allocator);
/* k_game_state_render_region  */ REFERENCE_DECLARE(0x018F2F60, t_restricted_allocation_manager, g_particle_system_data_array_allocator);
/* k_game_state_render_region  */ REFERENCE_DECLARE(0x018F3498, t_restricted_allocation_manager, g_contrail_system_allocator);
/* k_game_state_render_region  */ REFERENCE_DECLARE(0x018F34A4, t_restricted_allocation_manager, g_contrail_location_allocator);
/* k_game_state_render_region  */ REFERENCE_DECLARE(0x018F34B0, t_restricted_allocation_manager, g_contrail_allocator);
/* k_game_state_render_region  */ REFERENCE_DECLARE(0x018F34BC, t_restricted_allocation_manager, g_contrail_profile_allocator);
/* k_game_state_render_region  */ REFERENCE_DECLARE(0x018F36BC, t_restricted_allocation_manager, g_particle_location_data_array_allocator);
/* k_game_state_render_region  */ REFERENCE_DECLARE(0x018F3774, t_restricted_allocation_manager, g_light_volume_system_allocator);
/* k_game_state_render_region  */ REFERENCE_DECLARE(0x018F3780, t_restricted_allocation_manager, g_light_volume_location_allocator);
/* k_game_state_render_region  */ REFERENCE_DECLARE(0x018F378C, t_restricted_allocation_manager, g_light_volume_allocator);
/* k_game_state_render_region  */ REFERENCE_DECLARE(0x018F3924, t_restricted_allocation_manager, g_beam_system_allocator);
/* k_game_state_render_region  */ REFERENCE_DECLARE(0x018F3930, t_restricted_allocation_manager, g_beam_location_allocator);
/* k_game_state_render_region  */ REFERENCE_DECLARE(0x018F393C, t_restricted_allocation_manager, g_beam_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x018F4110, t_restricted_allocation_manager, g_ragdoll_data_allocator);
/* k_game_state_render_region  */ REFERENCE_DECLARE(0x0190ED18, t_restricted_allocation_manager, g_particle_emitter_data_array_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x01910138, t_restricted_allocation_manager, g_rasterizer_game_states_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x01910144, t_restricted_allocation_manager, g_hue_saturation_control_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x019134EC, t_restricted_allocation_manager, g_scripted_exposure_game_globals_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x019135EC, t_restricted_allocation_manager, g_hud_camera_globals_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x01914730, t_restricted_allocation_manager, g_water_interaction_event_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x01914810, t_restricted_allocation_manager, g_render_texture_camera_globals_allocator);
/* k_game_state_render_region  */ REFERENCE_DECLARE(0x01914938, t_restricted_allocation_manager, g_render_game_globals_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x019149F0, t_restricted_allocation_manager, g_depth_of_field_game_globals_allocator);
/* k_game_state_render_region  */ REFERENCE_DECLARE(0x01914AF8, t_restricted_allocation_manager, g_cached_object_render_states_allocator);
/* k_game_state_render_region  */ REFERENCE_DECLARE(0x01916178, t_restricted_allocation_manager, g_particle_emitter_gpu_x_data_array_manager);        // c_particle_emitter_gpu::x_data_array_manager
/* k_game_state_render_region  */ REFERENCE_DECLARE(0x01916184, t_restricted_allocation_manager, g_particle_emitter_gpu_s_row_x_data_array_manager);  // c_particle_emitter_gpu::s_row::x_data_array_manager
/* k_game_state_render_region  */ REFERENCE_DECLARE(0x019161B8, t_restricted_allocation_manager, g_particle_emitter_gpu_x_gamestate_storage_manager); // c_particle_emitter_gpu::x_gamestate_storage_manager
/* k_game_state_render_region  */ REFERENCE_DECLARE(0x01916738, t_restricted_allocation_manager, g_beam_gpu_x_data_array_manager);                    // c_beam_gpu::x_data_array_manager
/* k_game_state_render_region  */ REFERENCE_DECLARE(0x01916744, t_restricted_allocation_manager, g_beam_gpu_s_row_x_data_array_manager);              // c_beam_gpu::s_row::x_data_array_manager
/* k_game_state_render_region  */ REFERENCE_DECLARE(0x01916778, t_restricted_allocation_manager, g_beam_gpu_x_gamestate_storage_manager);             // c_beam_gpu::x_gamestate_storage_manager
/* k_game_state_render_region  */ REFERENCE_DECLARE(0x01917350, t_restricted_allocation_manager, g_contrail_gpu_x_data_array_manager);                // c_contrail_gpu::x_data_array_manager
/* k_game_state_render_region  */ REFERENCE_DECLARE(0x0191735C, t_restricted_allocation_manager, g_contrail_gpu_s_row_x_data_array_manager);          // c_contrail_gpu::s_row::x_data_array_manager
/* k_game_state_render_region  */ REFERENCE_DECLARE(0x01917390, t_restricted_allocation_manager, g_contrail_gpu_x_gamestate_storage_manager);         // c_contrail_gpu::x_gamestate_storage_manager
/* k_game_state_render_region  */ REFERENCE_DECLARE(0x01917790, t_restricted_allocation_manager, g_light_volume_gpu_x_data_array_manager);            // c_light_volume_gpu::x_data_array_manager
/* k_game_state_render_region  */ REFERENCE_DECLARE(0x0191779C, t_restricted_allocation_manager, g_light_volume_gpu_s_row_x_data_array_manager);      // c_light_volume_gpu::s_row::x_data_array_manager
/* k_game_state_render_region  */ REFERENCE_DECLARE(0x019177D0, t_restricted_allocation_manager, g_light_volume_gpu_x_gamestate_storage_manager);     // c_light_volume_gpu::x_gamestate_storage_manager
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x0191BDFC, t_restricted_allocation_manager, g_rasterizer_implicit_geometry_data_allocator);
/* k_global_render_data_region */ REFERENCE_DECLARE(0x0191C0FC, t_restricted_allocation_manager, g_render_object_globals_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x0191CA2C, t_restricted_allocation_manager, g_shield_render_cache_data_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x0191CCA4, t_restricted_allocation_manager, g_user_widget_allocator_0);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x0191CCB0, t_restricted_allocation_manager, g_user_widget_allocator_1);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x0191CCBC, t_restricted_allocation_manager, g_user_widget_allocator_2);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x0191CCC8, t_restricted_allocation_manager, g_user_widget_allocator_3);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x0191CCD4, t_restricted_allocation_manager, g_chud_persistent_user_data_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x0191CCE0, t_restricted_allocation_manager, g_chud_persistent_global_data_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x0191D370, t_restricted_allocation_manager, g_first_person_weapons_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x0191D37C, t_restricted_allocation_manager, g_first_person_weapon_orientations_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x01943678, t_restricted_allocation_manager, g_cortana_globals_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x0194396C, t_restricted_allocation_manager, g_campaign_objectives_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x019471E0, t_restricted_allocation_manager, g_object_message_queue_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x019471EC, t_restricted_allocation_manager, g_object_globals_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x019471F8, t_restricted_allocation_manager, g_object_header_data_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x01947204, t_restricted_allocation_manager, g_object_name_list_allocator);
/* k_game_state_render_region  */ REFERENCE_DECLARE(0x01947210, t_restricted_allocation_manager, g_object_render_data_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x0194721C, t_restricted_allocation_manager, g_object_memory_pool_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x01947228, t_restricted_allocation_manager, g_collideable_first_data_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x01947234, t_restricted_allocation_manager, g_collideable_data_reference_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x01947240, t_restricted_allocation_manager, g_collideable_cluster_reference_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x0194724C, t_restricted_allocation_manager, g_noncollideable_first_data_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x01947258, t_restricted_allocation_manager, g_noncollideable_data_reference_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x01947264, t_restricted_allocation_manager, g_noncollideable_cluster_reference_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x019478E0, t_restricted_allocation_manager, g_damage_globals_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x0194798C, t_restricted_allocation_manager, g_object_placement_globals_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x01949900, t_restricted_allocation_manager, g_device_groups_data_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x01949A2C, t_restricted_allocation_manager, g_object_scripting_state_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x01949AD8, t_restricted_allocation_manager, g_object_broadphase_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x01949C94, t_restricted_allocation_manager, g_object_schedule_globals_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x01949D40, t_restricted_allocation_manager, g_object_activation_region_data_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x01949E04, t_restricted_allocation_manager, g_light_first_data_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x01949E10, t_restricted_allocation_manager, g_light_data_reference_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x01949E1C, t_restricted_allocation_manager, g_light_cluster_reference_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x01949E28, t_restricted_allocation_manager, g_light_data_allocator);
/* k_game_state_render_region  */ REFERENCE_DECLARE(0x01949E34, t_restricted_allocation_manager, g_light_render_data_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x01949E40, t_restricted_allocation_manager, g_lights_game_globals_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x0194A230, t_restricted_allocation_manager, g_widget_data_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x0194A8F8, t_restricted_allocation_manager, g_recycling_groups_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x0194A904, t_restricted_allocation_manager, g_recycling_volumes_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x0194B030, t_restricted_allocation_manager, g_muffin_data_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x0194B370, t_restricted_allocation_manager, g_leaf_system_data_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x0194B418, t_restricted_allocation_manager, g_antenna_data_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x0194B4CC, t_restricted_allocation_manager, g_cloth_data_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x019923BC, t_restricted_allocation_manager, g_actor_data_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x019923C8, t_restricted_allocation_manager, g_ai_reference_frame_data_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x019923D4, t_restricted_allocation_manager, g_actor_firing_position_hash_allocator);
/* k_game_state_shared_region  */ REFERENCE_DECLARE(0x01992570, t_restricted_allocation_manager, g_ai_globals_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x01992624, t_restricted_allocation_manager, g_ai_players_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x019926DC, t_restricted_allocation_manager, g_team_dialogue_state_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x019926E8, t_restricted_allocation_manager, g_vocalization_record_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x01992A3C, t_restricted_allocation_manager, g_command_script_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x01992C30, t_restricted_allocation_manager, g_objectives_data_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x01992C3C, t_restricted_allocation_manager, g_tasks_data_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x019973DC, t_restricted_allocation_manager, g_squad_data_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x019973E8, t_restricted_allocation_manager, g_squad_group_data_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x019975C0, t_restricted_allocation_manager, g_swarm_data_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x019975CC, t_restricted_allocation_manager, g_swarm_spawners_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x019975D8, t_restricted_allocation_manager, g_spawner_globals_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x019978D4, t_restricted_allocation_manager, g_dynamic_firing_set_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x01997A6C, t_restricted_allocation_manager, g_prop_data_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x01997A78, t_restricted_allocation_manager, g_prop_ref_data_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x01997A84, t_restricted_allocation_manager, g_tracking_data_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x01997C0C, t_restricted_allocation_manager, g_joint_data_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x01997CF4, t_restricted_allocation_manager, g_clump_data_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x01997F0C, t_restricted_allocation_manager, g_squad_patrol_data_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x01998030, t_restricted_allocation_manager, g_flocks_data_allocator);
/* k_game_state_update_region  */ REFERENCE_DECLARE(0x01998130, t_restricted_allocation_manager, g_formation_data_allocator);
/* k_game_state_render_region  */ REFERENCE_DECLARE(0x019995F0, t_restricted_allocation_manager, g_vision_mode_state_allocator);

s_thread_local_storage* get_tls()
{
	static dword tls_index = 'NOGO';
	if (tls_index == 'NOGO')
	{
		byte* module_base = reinterpret_cast<byte*>(global_address_get(0));
		PIMAGE_DOS_HEADER dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(module_base);
		PIMAGE_NT_HEADERS nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(module_base + dos_header->e_lfanew);
		PIMAGE_TLS_DIRECTORY tls_directory = reinterpret_cast<PIMAGE_TLS_DIRECTORY>(module_base + nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress);
		tls_index = *reinterpret_cast<dword*>(tls_directory->AddressOfIndex);
	}

	if (tls_index == 'NOGO')
		return nullptr;

	void** tls_ptr = reinterpret_cast<void**>(__readfsdword(0x2C));
	return reinterpret_cast<s_thread_local_storage*>(tls_ptr[tls_index]);
}

// this is a pseudo implementation of `t_restricted_allocation_manager::reserve_memory`
void restricted_allocation_manager_reserve_memory(
	long index,
	void(__cdecl* tls_update_callback)(void*),
	void(__cdecl* tls_pre_overwrite_fixup_callback)(void*),
	void(__cdecl* tls_post_copy_fixup_callback)(void*),
	t_restricted_allocation_manager* allocator,
	char const* name,
	char const* type,
	unsigned int allocation,
	long alignment_bits,
	void* address
)
{
	ASSERT(!allocator->valid());

	allocator->m_member_index = restricted_region_add_member(index, name, type, allocation, alignment_bits, tls_update_callback, tls_pre_overwrite_fixup_callback, tls_post_copy_fixup_callback);
	allocator->m_thread_id = get_current_thread_index();
	address = restricted_region_get_member_address(index, allocator->m_member_index);
}

