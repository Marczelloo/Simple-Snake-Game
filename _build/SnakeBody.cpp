#include "SnakeBody.h";
#include "screens.h"
#include <raylib.h>

SnakeBody::SnakeBody() {
	this->position = { 0 , 0 };
	this->size = { 0, 0, };
	this->color = GREEN;
	this->colorFrame = DARKGREEN;
};

SnakeBody::SnakeBody(Vector2 position, Vector2 size, Color color, Color colorFrame)
{
	this->position = position;
	this->size = size;
	this->color = color;
	this->colorFrame = colorFrame;
}

void SnakeBody::Draw()
{
	DrawRectangle(position.x, position.y, size.x * gridSize, size.y * gridSize, color);
	DrawRectangleLines(position.x, position.y, size.x * gridSize, size.y * gridSize, colorFrame);
}

void SnakeBody::Move(Vector2 position)
{
	this->position = position;
}

void SnakeBody::Update(int framesCounter, Vector2 position)
{
	if (1)
	{
		Move(position);
	}
}

void SnakeBody::setPositon(Vector2 position)
{
	this->position = position;
}

Vector2 SnakeBody::getPosition()
{
	return position;
}

void SnakeBody::setSize(Vector2 size)
{
	this->size = size;
}

Vector2 SnakeBody::getSize()
{
	return size;
}

void SnakeBody::setColor(Color color)
{
	this->color = color;
}

Color SnakeBody::getColor()
{
	return color;
}

void SnakeBody::setColorFrame(Color color)
{
	this->colorFrame = color;
}

Color SnakeBody::getColorFrame()
{
	return colorFrame;
}