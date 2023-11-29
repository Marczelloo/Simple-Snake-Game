#pragma once

#include <raylib.h>
#include "Fruit.h"

enum Effect { NONE = 0, SPEEDUP = 1, SPEEDDOWN = 2, PASSING = 3, INVERTED = 4 };

class SpecialFruit: public Fruit{
	float duration;
	Effect effect;
	bool active;
public:
	SpecialFruit();
	SpecialFruit(Vector2, Vector2, Color, float, Effect);
	
	void Draw();
	void SpawnNew(Vector2, SnakeBody*, int, Fruit);

	float getDuration();
	Effect getEffect();
	bool getActive();

	void setActive(bool active);

};