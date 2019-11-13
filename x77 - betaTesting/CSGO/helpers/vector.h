#ifndef VECTOR_H
#define VECTOR_H
#ifdef _WIN32
#pragma once
#endif

#define M_PI		3.14159265358979323846f
#define M_RADPI		57.295779513082f
#define M_PI_F		((float)(M_PI))
#define RAD2DEG(x)  ((float)(x) * (float)(180.f / M_PI_F))
#define DEG2RAD(x)  ((float)(x) * (float)(M_PI_F / 180.f))

class vector
{
public:

	float x, y, z;

	vector(void)
	{
		invalidate();
	}

	vector(float x, float y, float z)
	{
		this->x = x; this->y = y; this->z = z;
	}

	float& operator[](int i)
	{
		return ((float*)this)[i];
	}

	float operator[](int i) const
	{
		return ((float*)this)[i];
	}

	bool operator==(const vector& src) const
	{
		return (src.x == x) && (src.y == y) && (src.z == z);
	}

	bool operator!=(const vector& src) const
	{
		return (src.x != x) || (src.y != y) || (src.z != z);
	}

	vector& operator+=(const vector& v)
	{
		x += v.x; y += v.y; z += v.z;
		return *this;
	}

	vector& operator-=(const vector& v)
	{
		x -= v.x; y -= v.y; z -= v.z;
		return *this;
	}

	vector& operator*=(float fl)
	{
		x *= fl; y *= fl; z *= fl;
		return *this;
	}

	vector& operator*=(const vector& v)
	{
		x *= v.x; y *= v.y; z *= v.z;
		return *this;
	}

	vector& operator/=(const vector& v)
	{
		x /= v.x; y /= v.y; z /= v.z;
		return *this;
	}

	vector&	operator+=(float fl)
	{
		x += fl; y += fl; z += fl;
		return *this;
	}

	vector&	operator/=(float fl)
	{
		x /= fl; y /= fl; z /= fl;
		return *this;
	}

	vector&	operator-=(float fl)
	{
		x -= fl; y -= fl; z -= fl;
		return *this;
	}

	vector operator-(void) const
	{
		return vector(-x, -y, -z);
	}

	vector operator+(const vector& v) const
	{
		return vector(x + v.x, y + v.y, z + v.z);
	}

	vector operator-(const vector& v) const
	{
		return vector(x - v.x, y - v.y, z - v.z);
	}

	vector operator*(float fl) const
	{
		return vector(x * fl, y * fl, z * fl);
	}

	vector operator*(const vector& v) const
	{
		return vector(x * v.x, y * v.y, z * v.z);
	}

	vector operator/(float fl) const
	{
		return vector(x / fl, y / fl, z / fl);
	}

	vector operator/(const vector& v) const
	{
		return vector(x / v.x, y / v.y, z / v.z);
	}

	float length(void) const
	{
		return sqrt(x * x + y * y + z * z);
	}

	float length2d(void) const
	{
		return sqrt(x * x + y * y);
	}

	float dot(const vector& b) const
	{
		return (x * b.x + y * b.y + z * b.z);
	}

	void invalidate()
	{
		x = y = z = std::numeric_limits<float>::infinity();
	}

	void init(float x = 0.0f, float y = 0.0f, float z = 0.0f)
	{
		this->x = x; this->y = y; this->z = z;
	}

	float length_sqr(void) const
	{
		return (x * x + y * y + z * z);
	}

	bool is_zero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance &&
			y > -tolerance && y < tolerance &&
			z > -tolerance && z < tolerance);
	}

	inline vector normalize()
	{
		vector vector;
		float length = this->length();

		if (length != 0) {
			vector.x = x / length;
			vector.y = y / length;
			vector.z = z / length;
		} else {
			vector.x = vector.y = 0.0f; vector.z = 1.0f;
		}

		return vector;
	}

	float normalize_in_place();

};

inline float vector_normalize(vector& angle) {

	float length = angle.length();

	if (!length)
		angle.init();
	else
		angle /= length;

	return length;

}

inline void vector_subtract(const vector& a, const vector& b, vector& result)
{
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
}

inline void vector_clear(vector& a)
{
	a.x = a.y = a.z = 0.0f;
}

inline void vector_copy(const vector& src, vector& dst)
{
	dst.x = src.x;
	dst.y = src.y;
	dst.z = src.z;
}

inline void vector_add(const vector& a, const vector& b, vector& c)
{
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
}

inline void vector_angles(const vector& forward, vector& angles)
{

	float tmp, yaw, pitch;

	if (forward.y == 0 && forward.x == 0) {

		yaw = 0;

		if (forward.z > 0) {
			pitch = 270;
		} else {
			pitch = 90;
		}

	} else {

		yaw = RAD2DEG(atan2f(forward.y, forward.x));

		if (yaw < 0)
			yaw += 360;

		tmp = forward.length2d();
		pitch = RAD2DEG(atan2f(-forward.z, tmp));

		if (pitch < 0)
			pitch += 360;

	}

	angles[0] = pitch;
	angles[1] = yaw;
	angles[2] = 0;

}

inline vector cross_product(const vector& a, const vector& b)
{
	return vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

inline float vector::normalize_in_place()
{
	float radius = sqrt(x * x + y * y + z * z);

	float iradius = 1.f / (radius + FLT_EPSILON);

	x *= iradius;
	y *= iradius;
	z *= iradius;

	return radius;
}

inline void vector_angles(const vector& forward, vector& up, vector& angles) {

	vector left = cross_product(up, forward);
	left.normalize_in_place();

	float forwardDist = forward.length2d();

	if (forwardDist > 0.001f) {
		angles.x = atan2f(-forward.z, forwardDist) * 180 / M_PI;
		angles.y = atan2f(forward.y, forward.x) * 180 / M_PI;

		float up_z	= (left.y * forward.x) - (left.x * forward.y);
		angles.z	= atan2f(left.z, up_z) * 180 / M_PI;
	} else {
		angles.x = atan2f(-forward.z, forwardDist) * 180 / M_PI;
		angles.y = atan2f(-left.x, left.y) * 180 / M_PI;
		angles.z = 0;
	}

}

inline void angle_vectors(const vector& angles, vector* forward)
{
	assert(forward);

	float	sp, sy, cp, cy;

	sy = sin(DEG2RAD(angles[1]));
	cy = cos(DEG2RAD(angles[1]));

	sp = sin(DEG2RAD(angles[0]));
	cp = cos(DEG2RAD(angles[0]));

	forward->x = cp * cy;
	forward->y = cp * sy;
	forward->z = -sp;
}

inline float dot_product(const vector& a, const vector& b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

class __declspec(align(16))vector_aligned : public vector
{
public:

	inline vector_aligned(void) {};

	inline vector_aligned(float x, float y, float z)
	{
		init(x, y, z);
	}

	explicit vector_aligned(const vector& v)
	{
		init(v.x, v.y, v.z);
	}

	vector_aligned& operator=(const vector& v)
	{
		init(v.x, v.y, v.z);
		return *this;
	}

	float w;

};

class vector2d
{
public:
	float x, y;
};

#endif // !VECTOR_H