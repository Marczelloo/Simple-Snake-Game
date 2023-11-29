#include <raylib.h>

#include "Fruit.h"
#include "screens.h"
#include <cstdlib>
#include <ctime>

#include <iostream>


Fruit::Fruit()
{
	this->position = { 0, 0 };
	this->size = { 0, 0 };
	this->color = RED;
}

Fruit::Fruit(Vector2 position, Vector2 size, Color color)
{
	this->position = { position.x * gridSize + (gridSize - size.x) / 2, position.y * gridSize + (gridSize - size.y) / 2};
	this->size = { size.x * gridSize, size.y * gridSize };
	this->color = color;
}

void Fruit::Draw()
{
	DrawRectangle(position.x, position.y, size.x, size.y, color);
}

void Fruit::SpawnNew(Vector2 snakehead, SnakeBody* snakebody, int snakeBodySize)
{
	srand(time(0));
	int minRange = 0;
	int maxRangeX = maxGridSizeWidth;
	int maxRangeY = maxGridSizeHeight;

	std::cout << "body: " << snakebody[0].getPosition().x << " " << snakebody[0].getPosition().y << std::endl;
	std::cout << "head: " << snakehead.x << " " << snakehead.y << std::endl;

	int newRandomX = rand() % (maxRangeX - minRange) + minRange;
	int newRandomY = rand() % (maxRangeY - minRange) + minRange;

	if (newRandomX == snakehead.x)
	{
		while (newRandomX == snakehead.y)
		{
			newRandomX = rand() % (maxRangeX - minRange) + minRange;
		}
	}
	
	if (newRandomY == snakehead.y)
	{
		while (newRandomY == snakehead.y);
		{
			newRandomY = rand() % (maxRangeY - minRange) + minRange;
		}
	}

	for (int i = 0; i < snakeBodySize; i++)
	{
		if (newRandomY == snakebody[i].getPosition().y)
		{
			while (newRandomY == snakebody[i].getPosition().y)
			{
				newRandomY = rand() % (maxRangeY - minRange) + minRange;
			}
		}

		if (newRandomX == snakebody[i].getPosition().x)
		{
			while (newRandomX == snakebody[i].getPosition().x)
			{
				newRandomX = rand() % (maxRangeX - minRange) + minRange;
			}
		}
	}

	this->position = Vector2{ (float)newRandomX * gridSize + (gridSize - size.x) / 2 , (float)newRandomY * gridSize + (gridSize - size.y) / 2 };
}

void Fruit::setPosition(Vector2 position)
{
	this->position = position;
}

void Fruit::setSize(Vector2 size)
{
	this->size = size;
}

void Fruit::setColor(Color color)
{
	this->color = color;
}

Vector2 Fruit::getPosition()
{
	return position;
}

Vector2 Fruit::getSize()
{
	return size;
}

Color Fruit::getColor()
{
	return color;
}