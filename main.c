#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL/SDL.h>
#include <math.h>

#include "math/vec4.h"
#include "math/mat4.h"
#include "math/proj.h"


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

int width  = 320;
int height = 240;

struct mat4 proj;

inline void setPxl(
	SDL_Surface *buf, 
	int x, int y, 
	int c) // 0xAARRGGBB
{
	int i, *pxl;

	pxl = (int*) buf->pixels;
	i = x + y * width;
	pxl[i] = c;
}

struct vec4 unproject(struct vec4 p) 
{
	return proj_view(proj_normalize(mat4_mulv(proj, p)), width, height);
}

void drawLine2d(
	SDL_Surface *buf, 
	scalar x1, scalar y1,
	scalar x2, scalar y2)
{
	scalar dx, dy, x, y;

	if(x1 > x2)
		return drawLine2d(buf, x2, y2, x1, y1);

	dx = x2 - x1;
	dy = y2 - y1;

	for(x = x1; x <= x2; x++)
	{
		y = y1 + dy * (x - x1) / dx;
		setPxl(buf, (int) x, (int) y, 0xffffffff);
	}

	if(y1 > y2) 
	{
		x = x2;
		y = y2;
		x2 = x1;
		y2 = y1;
		x1 = x;
		y1 = y;
	}

	for(y = y1; y <= y2; y++)
	{
		x = x1 + dx * (y - y1) / dy;
		setPxl(buf, (int) x, (int) y, 0xffffffff);
	}
}

void drawLine3d(SDL_Surface *buf, struct vec4 a, struct vec4 b)
{
	struct vec4 ua, ub;
	ua = unproject(a);	
	ub = unproject(b);
	drawLine2d(buf, ua.x, ua.y, ub.x, ub.y);
}

int main(int argc, char **argv) 
{
	SDL_Surface *screen;
	SDL_Event event;
	struct vec4 cubeCenter, cube[8];
	scalar rota;
	struct mat4 rot;
	int i;

	SDL_Init( SDL_INIT_EVERYTHING ); 

	screen = SDL_SetVideoMode(width, height, 32, 0);

	proj = proj_perspective(45, (scalar) width / (scalar) height, 1, 10);

	cubeCenter = vec4_zero();

	while(1) 
	{
		rota = (scalar) SDL_GetTicks() / 1000.0;
		cubeCenter.z = 5 + sin(rota);
		rot = mat4_aangle(_vec4(0, 1, 0, 1), rota);

		cube[0] = vec4_add(mat4_mulv(rot, _vec4( 1, -1, 1, 0)), cubeCenter);
		cube[1] = vec4_add(mat4_mulv(rot, _vec4(-1, -1, 1, 0)), cubeCenter);
		cube[2] = vec4_add(mat4_mulv(rot, _vec4(-1,  1, 1, 0)), cubeCenter);
		cube[3] = vec4_add(mat4_mulv(rot, _vec4( 1,  1, 1, 0)), cubeCenter);

		cube[4] = vec4_add(mat4_mulv(rot, _vec4( 1, -1, -1, 0)), cubeCenter);
		cube[5] = vec4_add(mat4_mulv(rot, _vec4(-1, -1, -1, 0)), cubeCenter);
		cube[6] = vec4_add(mat4_mulv(rot, _vec4(-1,  1, -1, 0)), cubeCenter);
		cube[7] = vec4_add(mat4_mulv(rot, _vec4( 1,  1, -1, 0)), cubeCenter);

		SDL_FillRect(screen, 0, 0);

		drawLine3d(screen, cube[0], cube[1]);
		drawLine3d(screen, cube[0], cube[3]);
		drawLine3d(screen, cube[1], cube[2]);
		drawLine3d(screen, cube[2], cube[3]);

		drawLine3d(screen, cube[4], cube[5]);
		drawLine3d(screen, cube[4], cube[7]);
		drawLine3d(screen, cube[5], cube[6]);
		drawLine3d(screen, cube[6], cube[7]);

		drawLine3d(screen, cube[0], cube[4]);
		drawLine3d(screen, cube[1], cube[5]);
		drawLine3d(screen, cube[2], cube[6]);
		drawLine3d(screen, cube[3], cube[7]);

		SDL_Flip(screen);

		while(SDL_PollEvent(&event) != 0)
		{
			switch(event.type)
			{
				case (SDL_QUIT):
					SDL_Quit();
					return 0;
				default:
					break;
			}
		}
	}

	SDL_Quit(); 
	return 0;
}
