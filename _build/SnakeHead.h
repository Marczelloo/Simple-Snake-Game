#pragma once

#include "SnakeBody.h"
#include "Fruit.h"

enum Direction { LEFT, UP, RIGHT, DOWN };

class SnakeHead {
	Vector2 size = { 0, 0 };
	Vector2 position = { 0, 0 };
	Color color = { 0, 0, 0, 0 };
	Color colorFrame = { 0, 0, 0, 0 };
	Color colorTongue = { 163, 26, 16, 255 };
	Direction direction = RIGHT;
	int speed;
	bool canChangeDir = true;;
public:
	SnakeHead();
	SnakeHead(Vector2 , Vector2, Color, Color, Direction, int);
	void Draw();
	void Update(int);
	void Move();
	void HandleDirectionChange();
	bool CheckCollisionWithBody(SnakeBody*, int);
	bool CheckCollisionWithBarriers();
	bool CheckCollisionWithFruit(Fruit);

	void setPosition(Vector2 );
	void setSize(Vector2 );
	void setColor(Color );
	void setColorFrame(Color);
	void setDirection(Direction );
	void setSpeed(int );

	Vector2 getPosition();
	Vector2 getSize();
	Color getColor();
	Color getColorFrame();
	Direction getDirection();
	int getSpeed();
};

