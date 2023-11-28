#pragma once

#include <raylib.h>
#include "Fruit.h"

enum Effect { SPEEDUP, SPEEDDOWN, PASSING, INVERTED};

class SpecialFruit: public Fruit{
	float duration;
	Effect effect;
public:
	SpecialFruit();
	SpecialFruit(Vector2, Vector2, Color, float, Effect);
	
	void SpawnNew(Vector2, SnakeBody*, int);

	float getDuration();
	Effect getEffect();

};