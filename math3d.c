#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "math3d.h"

struct vec4 vec4_identity() 
{
	struct vec4 v;
	v.x = 0;
	v.y = 0;
	v.z = 0;
	v.w = 0;
	return v;
}

struct vec4 vec4_add(struct vec4 v, struct vec4 u) 
{
	struct vec4 t;
	t.x = v.x + u.x;
	t.y = v.y + u.y;
	t.z = v.z + u.z;
	t.w = v.w + u.w;
	return t;
}

struct vec4 vec4_mul(struct vec4 v, struct vec4 u) 
{
	struct vec4 t;
	t.x = v.x * u.x;
	t.y = v.y * u.y;
	t.z = v.z * u.z;
	t.w = v.w * u.w;
	return t;
}

struct vec4 vec4_muls(scalar s, struct vec4 v) 
{
	struct vec4 t;
	t.x = s * v.x;
	t.y = s * v.y;
	t.z = s * v.z;
	t.w = s * v.w;
	return t;
}


struct mat4 mat4_identity() 
{
	struct mat4 m;
	m.a = vec4_identity();
	m.b = vec4_identity();
	m.c = vec4_identity();
	m.d = vec4_identity();

	m.a.x = 1;
	m.b.y = 1;
	m.c.z = 1;
	m.d.w = 1;

	return m;
}

struct mat4 mat4_mul(struct mat4 m, struct mat4 n) 
{
	struct mat4 o;
	o.a.x = m.a.x * n.a.x + m.a.y * n.b.x + m.a.z * n.c.x + m.a.w * n.d.x;	
	o.a.y = m.a.x * n.a.y + m.a.y * n.b.y + m.a.z * n.c.y + m.a.w * n.d.y;
	o.a.z = m.a.x * n.a.z + m.a.y * n.b.z + m.a.z * n.c.z + m.a.w * n.d.z;
	o.a.w = m.a.x * n.a.w + m.a.y * n.b.w + m.a.z * n.c.w + m.a.w * n.d.w;
	o.b.x = m.b.x * n.a.x + m.b.y * n.b.x + m.b.z * n.c.x + m.b.w * n.d.x;	
	o.b.y = m.b.x * n.a.y + m.b.y * n.b.y + m.b.z * n.c.y + m.b.w * n.d.y;
	o.b.z = m.b.x * n.a.z + m.b.y * n.b.z + m.b.z * n.c.z + m.b.w * n.d.z;
	o.b.w = m.b.x * n.a.w + m.b.y * n.b.w + m.b.z * n.c.w + m.b.w * n.d.w;
	o.c.x = m.c.x * n.a.x + m.c.y * n.b.x + m.c.z * n.c.x + m.c.w * n.d.x;	
	o.c.y = m.c.x * n.a.y + m.c.y * n.b.y + m.c.z * n.c.y + m.c.w * n.d.y;
	o.c.z = m.c.x * n.a.z + m.c.y * n.b.z + m.c.z * n.c.z + m.c.w * n.d.z;
	o.c.w = m.c.x * n.a.w + m.c.y * n.b.w + m.c.z * n.c.w + m.c.w * n.d.w;
	o.d.x = m.d.x * n.a.x + m.d.y * n.b.x + m.d.z * n.c.x + m.d.w * n.d.x;	
	o.d.y = m.d.x * n.a.y + m.d.y * n.b.y + m.d.z * n.c.y + m.d.w * n.d.y;
	o.d.z = m.d.x * n.a.z + m.d.y * n.b.z + m.d.z * n.c.z + m.d.w * n.d.z;
	o.d.w = m.d.x * n.a.w + m.d.y * n.b.w + m.d.z * n.c.w + m.d.w * n.d.w;	
	return o;
}

struct vec4 mat4_mulv(struct mat4 m, struct vec4 v)
{
	struct vec4 u;
	u.x = m.a.x * v.x +	m.a.y * v.y + m.a.z * v.z +	m.a.w * v.w;
	u.y = m.b.x * v.x +	m.b.y * v.y + m.b.z * v.z +	m.b.w * v.w;
	u.z = m.c.x * v.x +	m.c.y * v.y + m.c.z * v.z +	m.c.w * v.w;
	u.w = m.d.x * v.x +	m.d.y * v.y + m.d.z * v.z +	m.d.w * v.w;
	return u;	
}

void vec4_debug_print(struct vec4 v) 
{
	printf("%f %f %f %f\n", v.x, v.y, v.z, v.w);
}

void mat4_debug_print(struct mat4 m) 
{
	vec4_debug_print(m.a);
	vec4_debug_print(m.b);
	vec4_debug_print(m.c);
	vec4_debug_print(m.d);
}
