#include "proj.h"

// Set a perspective frustum
struct mat4 proj_frustum(
	scalar l, scalar r, // Left, Right
	scalar b, scalar t, // Bottom, Top
	scalar n, scalar f) // Near, Far
{
	struct mat4 m;
	m = mat4_identity();
	m.a.x = 2 * n / (r - l);
	m.a.z = (r + l) / (r - l);
	m.b.y = 2 * n / (t - b);
	m.b.z = (t + b) / (t - b);
	m.c.z = -(f + n) / (f - n);
	m.c.w = -(2 * f * n) / (f - n);
	m.d.z = -1;
	m.d.w = 0;
	return m;
}

// Normalize device Coords
struct vec4 proj_normalize(struct vec4 v)
{
	struct vec4 u;
	u.x = v.x / v.w;
	u.y = v.y / v.w;
	u.z = v.z / v.w;
	u.w = 0;
	return u;
}

// Get screen Coords from normalized
struct vec4 proj_view(struct vec4 v, scalar width, scalar height) 
{
	struct vec4 u;
	u.x = (width / 2) * v.x + (width / 2);
	u.y = (height / 2) * v.y + (height / 2);
	u.z = 0;
	u.w = 0;
	return u;
}

