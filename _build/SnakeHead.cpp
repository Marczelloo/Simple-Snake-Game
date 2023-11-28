#include <raylib.h>
#include <vector>
#include <iostream>
#include "SnakeHead.h"
#include "screens.h"

SnakeHead::SnakeHead() 
{
	this->size = { 0, 0 };
	this->position = { 0, 0 };
	this->color = GREEN;
	this->colorFrame = DARKGREEN;
	this->direction = RIGHT;
	this->speed = 1;
};

SnakeHead::SnakeHead(Vector2 position, Vector2 size, Color color, Color colorFrame, Direction direction, int speed)
{
	this->size = { size.x * gridSize, size.y * gridSize};
	this->position = { position.x * gridSize, position.y * gridSize };
	this->color = color;
	this->colorFrame = colorFrame;
	this->direction = direction;
	this->speed = speed;
}

void SnakeHead::Draw()
{
	DrawRectangle(position.x, position.y, size.x, size.y , color);
	DrawRectangleLines(position.x, position.y, size.x, size.y, colorFrame);

	switch (direction)
	{
	case UP:
		DrawRectangle(position.x + size.x / 2 - size.x / 4 / 2, 
			position.y - size.y / 2, 
			size.x / 4, 
			size.y / 2, 
			colorTongue );
		DrawRectangle(position.x + size.x / 4 - size.x / 4 / 2, 
			position.y + size.y / 4 - size.y / 4 / 2, 
			size.x / 4, 
			size.y / 4, 
			BLACK);
		DrawRectangle(position.x + size.x - size.x / 4 - size.x / 4 / 2, 
			position.y + size.y / 4 - size.y / 4 / 2, 
			size.x / 4, 
			size.y / 4, 
			BLACK);
		break;
	case RIGHT:
		DrawRectangle(position.x + size.x, position.y + size.y / 2 - size.y / 4 / 2, size.x / 2, size.y / 4, colorTongue);
		DrawRectangle(position.x + size.x - size.x / 4 - size.x / 4 / 2,
			position.y + size.y / 4 - size.y / 4 / 2,
			size.x / 4,
			size.y / 4,
			BLACK);
		DrawRectangle(position.x + size.x - size.x / 4 - size.x / 4 / 2,
			position.y + size.y / 2 + size.y / 4 - size.y / 4 / 2,
			size.x / 4,
			size.y / 4,
			BLACK);
		break;
	case DOWN:
		DrawRectangle(position.x + size.x / 2 - size.x / 4 / 2, position.y + size.y, size.x / 4, size.y / 2, colorTongue);
		DrawRectangle(position.x + size.x / 4 - size.x / 4 / 2, 
			position.y + size.y - size.y / 4 - size.y / 4 / 2, 
			size.x / 4,
			size.y / 4, 
			BLACK);
		DrawRectangle(position.x + size.x - size.x / 4 - size.x / 4 / 2, 
			position.y + size.y - size.y / 4 - size.y / 4 / 2, 
			size.x / 4, 
			size.y / 4, 
			BLACK);
		break;
	case LEFT:
		DrawRectangle(position.x - size.x / 2, position.y + size.y / 2 - size.y / 4 / 2, size.x / 2, size.y / 4, colorTongue);
		DrawRectangle(position.x + size.x / 4 - size.x / 4 / 2,
			position.y + size.y / 4 - size.y / 4 / 2,
			size.x / 4,
			size.y / 4,
			BLACK);
		DrawRectangle(position.x + size.x / 4 - size.x / 4 / 2,
			position.y + size.y / 2 + size.y / 4 - size.y / 4 / 2,
			size.x / 4,
			size.y / 4,
			BLACK);
		break;
	}
}

void SnakeHead::Move()
{
	switch (direction)
	{
	case LEFT:
		position.x -= speed * gridSize;
		break;
	case UP:
		position.y -= speed * gridSize;
		break;
	case RIGHT:
		position.x += speed * gridSize;
		break;
	case DOWN:
		position.y += speed * gridSize;
		break;
	}
}

void SnakeHead::HandleDirectionChange()
{
	if (canChangeDir)
	{
		if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))
		{
			if (direction == DOWN) return;
			direction = UP;
			canChangeDir = false;
		}

		if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))
		{
			if (direction == UP) return;
			direction = DOWN;
			canChangeDir = false;

		}

		if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT))
		{
			if (direction == RIGHT) return;
			direction = LEFT;
			canChangeDir = false;
		}

		if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT))
		{
			if (direction == LEFT) return;
			direction = RIGHT;
			canChangeDir = false;
		}
	}
}
void SnakeHead::Update(int framesCounter)
{
	HandleDirectionChange();
	if (framesCounter % 10 == 0)
	{
		Move();
		canChangeDir = true;
	}
}

bool SnakeHead::CheckCollisionWithBody(SnakeBody* snakebody, int snakeBodySize)
{
	Rectangle headRec{ position.x, position.y, size.x, size.y };
		
	for (int i = 0; i < snakeBodySize; i++)
	{		
		Rectangle bodyRec{
			snakebody[i].getPosition().x,
			snakebody[i].getPosition().y, 
			snakebody[i].getSize().x * gridSize,
			snakebody[i].getSize().y * gridSize
		};
		
		if (CheckCollisionRecs(headRec, bodyRec)) return true;
	}

	return false;
}

bool SnakeHead::CheckCollisionWithFruit(Fruit fruit)
{
	Rectangle headRec{ position.x, position.y, size.x, size.y };
	Rectangle fruitRec{
		fruit.getPosition().x,
		fruit.getPosition().y,
		fruit.getSize().x,
		fruit.getSize().y
	};

	if (CheckCollisionRecs(headRec, fruitRec)) return true;

	return false;
}

bool SnakeHead::CheckCollisionWithBarriers()
{
	if (position.x >= screenWidth || position.x < 0) return true;
	if (position.y >= screenHeight || position.y < 0) return true;

	/*if (position.x > screenWidth)
	{
		position.x = 0;
	}
	if (position.x < 0)
	{
		position.x = screenWidth;
	}
	if (position.y > screenHeight)
	{
		position.y = 0;
	}
	if (position.y < 0)
	{
		position.y = screenHeight;
	}
	*/
	return false;
}

void SnakeHead::setPosition(Vector2 newPos)
{
	this->position = newPos;
}

void SnakeHead::setSize(Vector2 newSize)
{
	this->size = newSize;
}

Vector2 SnakeHead::getPosition()
{
	return position;
}

Vector2 SnakeHead::getSize()
{
	return size;
}

Direction SnakeHead::getDirection()
{
	return direction;
}

void SnakeHead::setDirection(Direction direction)
{
	this->direction = direction;
}

Color SnakeHead::getColor()
{
	return color;
}

void SnakeHead::setColor(Color color)
{
	this->color = color;
}

int SnakeHead::getSpeed()
{
	return speed;
}

void SnakeHead::setSpeed(int speed)
{
	this->speed = speed;
}

Color SnakeHead::getColorFrame()
{
	return colorFrame;
}

void SnakeHead::setColorFrame(Color colorFrame)
{
	this->colorFrame = colorFrame;
}



