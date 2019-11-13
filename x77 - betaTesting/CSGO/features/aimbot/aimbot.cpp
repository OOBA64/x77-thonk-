#include "../../main.h"


namespace a
{

	vector get_hitbox_pos(c_baseentity* target, int id)
	{

		matrix3x4_t matrix[MAXSTUDIOBONES];

		if (target->setup_bones(matrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, i::globals->curtime)) {

			if (target->get_model() != nullptr) {

				studiohdr_t* hdr = i::modelinfo->get_studio_model(target->get_model());

				if (hdr != nullptr) {

					mstudiohitboxset_t* set		= hdr->get_hitbox_set(0);
					mstudiobbox_t*		hitbox	= set->get_hitbox(id);

					if (hitbox) {

						vector min, max, center;

						u::vector_transform(hitbox->bbmin, matrix[hitbox->bone], min);
						u::vector_transform(hitbox->bbmax, matrix[hitbox->bone], max);

						center = (min + max) * 0.5;

						return center;

					}

				}

			}

		}

		return vector(0, 0, 0);

	}

	bool is_visible(c_baseentity* ent, vector start, vector end)
	{

		trace_t			trace;
		ray_t			ray;
		trace_filter	filter(g::local);

		ray.init(start, end);

		i::enginetrace->trace_ray(ray, MASK_SHOT, &filter, &trace);

		return (trace.ent == ent || trace.fraction >= 0.99f);

	}

	bool is_visible_length(c_baseentity* ent, vector start, vector end)
	{

		trace_t			trace;
		ray_t			ray;
		trace_filter	filter(g::local);

		vector start_pos, end_bone, end_pos[3];
		start_pos	= start;
		end_bone	= end;

		if (is_visible(ent, start, end)) return true;

		ray.init(start, end);

		i::enginetrace->trace_ray(ray, MASK_SHOT, &filter, &trace);

		end_pos[0] = trace.end_pos;

		ray.init(end_bone, start_pos);
		filter.skip = ent;
		i::enginetrace->trace_ray(ray, MASK_SHOT, &filter, &trace);

		end_pos[1] = trace.end_pos;

		vector_subtract(end_pos[0], end_pos[1], end_pos[2]);

		float length = end_pos[2].length();

		if (trace.fraction != 0)
			if (length < 13)
				return true;

		return false;

	}

	bool can_shoot()
	{

		float server_time;

		server_time = (float)(g::local->get_tick_base() * i::globals->interval_per_tick);

		if (g::local->get_active_weapon() == nullptr) return false;

		if (g::local->get_active_weapon()->is_reloading() ||
			g::local->get_active_weapon()->clip1() <= 0 ||
			g::local == nullptr) return false;

		return g::local->get_active_weapon()->next_primary_attack() <= server_time;

	}

	bool hit_chance(c_baseentity* entity, base_weapon* weapon, vector ang, vector point, int chance)
	{

		if (chance == 0 || vars::aim::aim_hitchance_amt == 0) return true;

		float seeds = 256.f;

		if (entity != nullptr && weapon != nullptr) {

			ang -= (g::local->get_aim_punch_angle() * 2.f);

			vector forward, right, up;

			u::angle_vectors(ang, &forward, &right, &up);

			int hits = 0, needed_hits = (seeds * (chance / 100.f));

			float weap_spread = weapon->get_spread(), weap_inaccuracy = weapon->get_inaccuracy();

			for (int i = 0; i < seeds; i++) {

				float inaccuracy	= u::random_float(0.f, 1.f) * weap_inaccuracy;
				float spread		= u::random_float(0.f, 1.f) * weap_spread;

				vector spread_view((cos(u::random_float(0.f, 2.f * M_PI)) * inaccuracy) + (cos(u::random_float(0.f, 2.f * M_PI)) * spread), (sin(u::random_float(0.f, 2.f * M_PI)) * inaccuracy) + (sin(u::random_float(0.f, 2.f * M_PI)) * spread), 0), direction;
				direction = vector(forward.x + (spread_view.x * right.x) + (spread_view.y * up.x), forward.y + (spread_view.x * right.y) + (spread_view.y * up.y), forward.z + (spread_view.x * right.z) + (spread_view.y * up.z)).normalize();

				vector viewangles_spread, view_forward;

				vector_angles(direction, up, viewangles_spread);
				u::angle_normalize(viewangles_spread);

				u::angle_vectors(viewangles_spread, &view_forward);
				view_forward.normalize_in_place();

				view_forward = g::local->get_eye_position() + (view_forward * weapon->get_cs_wpn_info()->range);

				trace_t	trace;

				i::enginetrace->clip_ray_to_entity(ray_t(g::local->get_eye_position(), view_forward), MASK_SHOT | CONTENTS_GRATE, entity, &trace);

				if (trace.ent == entity)
					hits++;

				if (((hits / seeds) * 100.f) >= chance)
					return true;

				if ((seeds - i + hits) < needed_hits)
					return false;

			}

		}


		return false;

	}

	void do_auto_revolver()
	{

		auto id = g::local->get_active_weapon();

		if (!vars::aim::aim_enabled || !vars::aim::aim_auto_revolver) return;

		if (id != nullptr) {

			if (g::cmd->buttons & IN_ATTACK || g::cmd->buttons & IN_RELOAD) return;

			if (can_shoot() && id->item_definition_index() == WEAPON_REVOLVER) {

				static int delay = 0;
				delay++;

				auto postponefireready = id->get_fire_ready_time();
				if (postponefireready > 0 && (postponefireready - 1.f < i::globals->curtime)) {
					g::cmd->buttons &= ~IN_ATTACK;
				}

				if (delay <= 15)
					g::cmd->buttons |= IN_ATTACK;
				else
					delay = 0;

			}

		}

	}

	void do_aimbot()
	{

		vector	begin, end, dir, ang;
		auto	wep = g::local->get_active_weapon();

		// movement
		vector	old_angle			= g::cmd->viewangles;
		float	old_forward_move	= g::cmd->forwardmove, old_side_move = g::cmd->sidemove;

		// make sure aimbot is enabled before continuing
		if (!vars::aim::aim_enabled) return;

		if (g::target != nullptr && wep != nullptr) {

			begin	= g::local->get_eye_position() + (g::local->get_velocity() * i::globals->interval_per_tick);
			end		= get_hitbox_pos(g::target, get_hitboxes(g::target)) + (g::target->get_velocity() * i::globals->interval_per_tick);
			dir		= end - begin;

			vector_normalize(dir);

			vector_angles(dir, ang);

			// rcs
			if (g::local->get_aim_punch_angle().length2d() > 0 && g::local->get_aim_punch_angle().length2d() < 150)
				ang -= g::local->get_aim_punch_angle() * 2.f;

			// smooth
			if (vars::aim::aim_smooth > 0.0f) {

				vector delta(g::cmd->viewangles - ang);

				u::angle_normalize(delta);

				ang = g::cmd->viewangles - delta / vars::aim::aim_smooth;

			}

			// check for shoot button
			if (vars::aim::aim_on_attack && !(g::cmd->buttons & IN_ATTACK)) return;

			// hitchance check for our autostop
			if (hit_chance(g::target, wep, ang, end, 1))
				g::lowest_accuracy = true;
			else
				g::lowest_accuracy = false;

			if (can_shoot()) {

				if (vars::aim::aim_auto_scope) {

					if (g::local->get_active_weapon()->get_cs_wpn_info()->weapon_type == WEAPONTYPE_SNIPER_RIFLE) {
						if (!g::local->is_scoped() && (g::local->get_flags() & FL_ONGROUND) && can_shoot() && g::lowest_accuracy)
							g::cmd->buttons |= IN_ATTACK2;
					}

				}

				if (hit_chance(g::target, wep, ang, end, vars::aim::aim_hitchance_amt)) {

					// set our aim angle
					g::cmd->viewangles = ang;

					// set our aim angle (non-silent)
					if (!vars::aim::aim_silent)
						i::engineclient->set_view_angles(ang);

					// shoot
					if (vars::aim::aim_auto_shoot)
						g::cmd->buttons |= IN_ATTACK;

				}

			}

		}

		u::fix_movement(old_angle, old_forward_move, old_side_move);

	}

	void do_auto_stop()
	{

		// validate weapon handle
		if (g::local->get_active_weapon() == nullptr) return;

		vector velocity = g::local->get_velocity(), direction, view, forward;

		vector_angles(velocity, direction);
		i::engineclient->get_view_angles(view);

		if (velocity.length() == 0)
			return;

		 static float speed = 450.f;

		direction.y = view.y - direction.y;

		angle_vectors(direction, &forward);

		vector negated_direction = forward * -speed;

		if (g::target != nullptr) {

			if (!g::lowest_accuracy) return;

			if (vars::aim::aim_enabled && vars::aim::aim_auto_stop) {
				if (can_shoot() && g::local->get_active_weapon()->is_gun() && (g::local->get_flags() & FL_ONGROUND)) {
					g::cmd->forwardmove = negated_direction.x;
					g::cmd->sidemove	= negated_direction.y;
				}
			}

		}

	}

	int get_target()
	{

		player_info_t	info;
		vector			begin, end;
		int				target	= -1;
		auto			wep		= g::local->get_active_weapon();

		for (auto i = 1; i <= i::globals->max_clients; i++) {

			auto entity = reinterpret_cast<c_baseentity*>(i::entitylist->get_client_entity(i));

			// validate entity
			if (!entity) continue;

			// dormant check
			if (entity->is_dormant()) continue;

			// local player check
			if (entity->get_index() == g::local->get_index()) continue;

			// verify weapon handle
			if (g::local->get_active_weapon() == nullptr) continue;

			// make sure they're a player
			if (!i::engineclient->get_player_info(i, &info)) continue;

			// make sure they're alive
			if (entity->get_health() <= 0 || entity->get_life_state() != LIFE_ALIVE) continue;

			// make sure they're not on our team
			if (!vars::aim::aim_target_teammates && entity->get_team_num() == g::local->get_team_num()) continue;

			// make sure they're not immune (deathmatch)
			if (entity->is_immune()) continue;

			// in air check
			if (vars::aim::aim_ignore_jumping && !(entity->get_flags() & FL_ONGROUND)) continue;

			// check class id
			if (entity->get_client_class()->class_id != CCSPlayer) continue;

			// make sure we have a pointer to their model
			if (!i::modelinfo->get_studio_model(entity->get_model())) continue;

			// grab information for our fov+vis check
			begin	= g::local->get_eye_position() + (g::local->get_velocity() * i::globals->interval_per_tick);
			end		= get_hitbox_pos(entity, get_hitboxes(entity)) + (entity->get_velocity() * i::globals->interval_per_tick);

			if (u::get_fov(g::cmd->viewangles, begin, end) <= vars::aim::aim_fov && 
				u::get_distance(entity->get_abs_origin(), g::local->get_abs_origin()) <= wep->get_cs_wpn_info()->range) {

				if (is_visible_length(entity, begin, end))
					target = i; // grab any player within our fov that is visible

			}

		}

		return target;

	}


	int	get_hitboxes(c_baseentity* target)
	{

		std::vector<int> scan;

		if (vars::aim::aim_hitbox == 1) {
			scan.push_back(HITBOX_HEAD);
		} else if (g::local->get_active_weapon()->item_definition_index() == WEAPON_TASER) {
			scan.push_back(HITBOX_CHEST);
		} else if (vars::aim::aim_hitbox == 2) {

			// torso
			scan.push_back(HITBOX_UPPER_CHEST);
			scan.push_back(HITBOX_CHEST);
			scan.push_back(HITBOX_LOWER_CHEST);
			scan.push_back(HITBOX_STOMACH);
			scan.push_back(HITBOX_PELVIS);

			// arms
			scan.push_back(HITBOX_LEFT_FOREARM);
			scan.push_back(HITBOX_LEFT_UPPER_ARM);
			scan.push_back(HITBOX_LEFT_FOREARM);
			scan.push_back(HITBOX_LEFT_UPPER_ARM);

			// hands
			scan.push_back(HITBOX_RIGHT_HAND);
			scan.push_back(HITBOX_LEFT_HAND);

			// legs
			scan.push_back(HITBOX_LEFT_CALF);
			scan.push_back(HITBOX_LEFT_THIGH);
			scan.push_back(HITBOX_RIGHT_CALF);
			scan.push_back(HITBOX_RIGHT_THIGH);

		} else {

			// torso
			scan.push_back(HITBOX_HEAD);
			scan.push_back(HITBOX_UPPER_CHEST);
			scan.push_back(HITBOX_CHEST);
			scan.push_back(HITBOX_LOWER_CHEST);
			scan.push_back(HITBOX_STOMACH);
			scan.push_back(HITBOX_PELVIS);

			// arms
			scan.push_back(HITBOX_LEFT_FOREARM);
			scan.push_back(HITBOX_LEFT_UPPER_ARM);
			scan.push_back(HITBOX_LEFT_FOREARM);
			scan.push_back(HITBOX_LEFT_UPPER_ARM);

			// hands
			scan.push_back(HITBOX_RIGHT_HAND);
			scan.push_back(HITBOX_LEFT_HAND);

			// legs
			scan.push_back(HITBOX_LEFT_CALF);
			scan.push_back(HITBOX_LEFT_THIGH);
			scan.push_back(HITBOX_RIGHT_CALF);
			scan.push_back(HITBOX_RIGHT_THIGH);

		}

		// return shootable hitbox
		for (auto i : scan) {
			if (is_visible_length(target, g::local->get_eye_position(), get_hitbox_pos(target, i)))
				return i;
		}

	}


}
