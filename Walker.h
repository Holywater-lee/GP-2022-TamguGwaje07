#pragma once

#ifdef _VS
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#else
#include "usr/include/SDL2/SDL.h"
#include "usr/include/SDL2/SDL2_gfxPrimitives.h"
#endif

#include "Vector2D.h"

class Walker
{
public:
	Walker(float x, float y);
	void draw(SDL_Renderer* renderer);
	void update();
	void applyForce(Vector2D force);
	void seek(Vector2D target);
	void edges();

private:
	Vector2D acceleration;
	Vector2D velocity;
	Vector2D location;
	const int r;
	const float maxForce;
	const float maxSpeed;
	float heading = 0;
};