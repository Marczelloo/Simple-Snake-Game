#pragma once

#include "SnakeBody.h"
#include "Fruit.h"
#include "SpecialFruit.h"

enum Direction { LEFT, UP, RIGHT, DOWN };

struct SnakeEffect
{
	Effect effect;
	float duration;
	float maxDuration;
};

class SnakeHead {
	Vector2 size = { 0, 0 };
	Vector2 position = { 0, 0 };
	Color color = { 0, 0, 0, 0 };
	Color colorFrame = { 0, 0, 0, 0 };
	Color colorTongue = { 163, 26, 16, 255 };
	Direction direction = RIGHT;
	int speed;
	int frameSpeed = 10;
	bool canChangeDir = true;
	SnakeEffect snakeEffects[4];
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
	bool CheckCollisionWithSpecialFruit(SpecialFruit);
	void UpdateEffectDuration();
	void DrawEffects();

	void setPosition(Vector2 );
	void setSize(Vector2 );
	void setColor(Color );
	void setColorFrame(Color);
	void setDirection(Direction );
	void setSpeed(int );
	void setSnakeEffects(SnakeEffect[4]);
	void addEffect(Effect, float);
	void setFrameSpeed(int frameSpeed);

	Vector2 getPosition();
	Vector2 getSize();
	Color getColor();
	Color getColorFrame();
	Direction getDirection();
	int getSpeed();
	SnakeEffect* getSnakeEffects();
	int getFrameSpeed();
	
};

