#ifndef PROJ_H
#define PROJ_H

/*
 * This file contains functions to set up and use a projection matrix.
*/

#include "mat4.h"

// Set a perspective frustum
struct mat4 proj_frustum(
	scalar, scalar, // Left, Right
	scalar, scalar, // Bottom, Top
	scalar, scalar); // Near, Far

// Normalize device Coords
struct vec4 proj_normalize(struct vec4 v);

// Get screen Coords from normalized
struct vec4 proj_view(struct vec4, scalar, scalar);

#endif
