#include "..//..//main.h"

std::vector<std::pair<c_baseentity*, vector>> player_data;

namespace resolver
{

	bool is_fake_ducking(c_baseentity* entity)
	{
		return (entity->get_duck_speed() == 8 && (entity->get_duck_amount() > 0.1 && entity->get_duck_amount() <= 0.9));
	}

	void resolver(client_frame_stage_t stage)
	{

		if (stage && vars::hvh::hvh_resolver) {

			for (auto i = 1; i <= i::globals->max_clients; i++) {

				auto entity = reinterpret_cast<c_baseentity*>(i::entitylist->get_client_entity(i));

				if (entity == nullptr || entity->get_index() == g::local->get_index()) continue;

				if (entity->get_life_state() != LIFE_ALIVE || entity->get_health() <= 0) continue;

				if (entity->is_dormant()) continue;

				vector* ang = entity->get_eye_angles_ptr();

				// force eye angles to lby
				ang->y = entity->get_lower_body_yaw();

				//  Burn ze jews?? I think I fucking wrote this idk -OOBAA #shorttermmemeoryloss XD LOL ROFL 
				if (g::target != nullptr && 
					(entity->get_index() == g::target->get_index())) {
					switch (g::shots_missed) {
					case 1:
						ang->y += 180.f;
						break;
					case 2:
						ang->y -= entity->get_max_desync_delta();
						break;
					case 3:
						ang->y += entity->get_max_desync_delta();
						break;
					}
				}

			}

		}

	}

}