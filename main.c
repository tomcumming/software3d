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

void drawPoint(SDL_Surface *buf, struct vec4 v) 
{
	struct vec4 f, n, vw;

	f = mat4_mulv(proj, v);
	n = proj_normalize(f);
	vw = proj_view(n, width, height);

	if(vw.x < 0 || vw.x >= width || vw.y < 0 || vw.y >= height) 
	{
		return; // Clipped
	}
	
	setPxl(buf, (int) vw.x, (int) vw.y, 0xffffffff);
}

int main(int argc, char **argv) 
{
	SDL_Surface *screen;
	SDL_Event event;
	struct vec4 cubeCenter, cube[8];
	int i;

	SDL_Init( SDL_INIT_EVERYTHING ); 

	screen = SDL_SetVideoMode(width, height, 32, 0);

	proj = proj_perspective(45, (scalar) width / (scalar) height, 1, 10);

	cubeCenter = vec4_zero();

	while(1) 
	{
		cubeCenter.z = 5 + sin((scalar) SDL_GetTicks() / 1000.0);

		cube[0] = vec4_add(cubeCenter, _vec4( 1, -1, 1, 0));
		cube[1] = vec4_add(cubeCenter, _vec4(-1, -1, 1, 0));
		cube[2] = vec4_add(cubeCenter, _vec4(-1,  1, 1, 0));
		cube[3] = vec4_add(cubeCenter, _vec4( 1,  1, 1, 0));

		cube[4] = vec4_add(cubeCenter, _vec4( 1, -1, -1, 0));
		cube[5] = vec4_add(cubeCenter, _vec4(-1, -1, -1, 0));
		cube[6] = vec4_add(cubeCenter, _vec4(-1,  1, -1, 0));
		cube[7] = vec4_add(cubeCenter, _vec4( 1,  1, -1, 0));

		SDL_FillRect(screen, 0, 0);

		for(i = 0; i < 8; i++) 
			drawPoint(screen, cube[i]);

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
