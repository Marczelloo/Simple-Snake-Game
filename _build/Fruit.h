#pragma once

#include <raylib.h>

#include "SnakeBody.h"

class Fruit { 
	Vector2 position;
	Vector2 size;
	Color color;
public:
	Fruit();
	Fruit(Vector2, Vector2, Color);
	void Draw();
	void SpawnNew(Vector2, SnakeBody*, int);

	void setPosition(Vector2);
	void setSize(Vector2);
	void setColor(Color);

	Vector2 getPosition();
	Vector2 getSize();
	Color getColor();


};
