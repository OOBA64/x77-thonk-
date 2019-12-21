#include "..//..//main.h"

namespace u
{

	void fix_movement(vector ang)
	{

		vector ang_move, move(g::cmd->forwardmove, g::cmd->sidemove, g::cmd->upmove);

		float speed = move.length2d();

		vector_angles(move, ang_move);

		float yaw = DEG2RAD(ang.y - g::cmd->viewangles.y + ang_move.y);

		g::cmd->forwardmove = cos(yaw) * speed;
		g::cmd->sidemove = sin(yaw) * speed;

	}

	void fix_movement(vector old_angles, float old_forward, float old_side_move) {

		float delta_view = g::cmd->viewangles.y - old_angles.y;
		float f1;
		float f2;

		if (old_angles.y < 0.f) {
			f1 = 360.0f + old_angles.y;
		} else {
			f1 = old_angles.y;
		}

		if (g::cmd->viewangles.y < 0.0f) {
			f2 = 360.0f + g::cmd->viewangles.y;
		} else {
			f2 = g::cmd->viewangles.y;
		}

		if (f2 < f1) {
			delta_view = abs(f2 - f1);
		} else {
			delta_view = 360.0f - abs(f1 - f2);
		}

		delta_view = 360.0f - delta_view;

		g::cmd->forwardmove	= cos(u::degree_to_radian(delta_view)) * old_forward + cos(u::degree_to_radian(delta_view + 90.f)) * old_side_move;
		g::cmd->sidemove	= sin(u::degree_to_radian(delta_view)) * old_forward + sin(u::degree_to_radian(delta_view + 90.f)) * old_side_move;

	}

	float get_fov(const vector& ang, const vector& start, const vector& end) {

		vector	angle,
				aim,
				dir = end - start;

		vector_normalize(dir);
		vector_angles(dir, angle);

		u::make_vector(ang, aim);
		u::make_vector(angle, angle);

		return u::radius_to_degree(acos(aim.dot(angle)) / aim.length_sqr());

	}

}