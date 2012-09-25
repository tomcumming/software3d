#ifndef MATH_H
#define MATH_H

typedef float scalar;

struct vec4 {
	scalar x, y, z, w;
};

struct mat4 {
	struct vec4 a, b, c, d;
};

struct vec4 vec4_identity();
struct vec4 vec4_add(struct vec4, struct vec4);
struct vec4 vec4_mul(struct vec4, struct vec4);
struct vec4 vec4_muls(scalar, struct vec4);

struct mat4 mat4_identity();
struct mat4 mat4_mul(struct mat4, struct mat4); 
struct vec4 mat4_mulv(struct mat4, struct vec4);

void vec4_debug_print(struct vec4);
void mat4_debug_print(struct mat4);

#endif
