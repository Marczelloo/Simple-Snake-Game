#include "SpecialFruit.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "screens.h";


SpecialFruit::SpecialFruit() : Fruit()
{
	this->setSize({ 0, 0 });
	this->setPosition({ 0, 0 });
	this->setColor({ 0, 0, 0, 0 });
	this->duration = 0;
	this->effect = SPEEDUP;
}

SpecialFruit::SpecialFruit(Vector2 pos, Vector2 size, Color color, float durtation, Effect effect) : Fruit(pos, size, color)
{
	this->duration = durtation;
	this->effect = effect;
}

float SpecialFruit::getDuration()
{
	return duration;
}

Effect SpecialFruit::getEffect()
{
	return effect;
}

void SpecialFruit::SpawnNew(Vector2 snakehead, SnakeBody* snakebody, int snakeBodySize)
{	
	int min = 1;
	int max = 100;
	std::srand(std::time(0));
	int chance = min + (std::rand() % (max - min + 1));
	
	if (chance < 90) return;
	
	srand(time(0));
	int minRange = 0;
	int maxRangeX = maxGridSizeWidth;
	int maxRangeY = maxGridSizeHeight;

	int newRandomX = rand() % (maxRangeX - minRange) + minRange;
	int newRandomY = rand() % (maxRangeY - minRange) + minRange;

	if (newRandomX == snakebody->getPosition().x)
	{
		while (newRandomX != snakebody->getPosition().y)
		{
			newRandomX = rand() % (maxRangeX - minRange) + minRange;
		}
	}

	if (newRandomY == snakebody->getPosition().y)
	{
		while (newRandomY != snakebody->getPosition().y);
		{
			newRandomY = rand() % (maxRangeY - minRange) + minRange;
		}
	}

	for (int i = 0; i < snakeBodySize; i++)
	{
		if (newRandomY == snakebody[i].getPosition().y)
		{
			while (newRandomY != snakebody[i].getPosition().y)
			{
				newRandomY = rand() % (maxRangeY - minRange) + minRange;
			}
		}

		if (newRandomX == snakebody[i].getPosition().x)
		{
			while (newRandomX != snakebody[i].getPosition().x)
			{
				newRandomX = rand() % (maxRangeX - minRange) + minRange;
			}
		}
	}

	int min_e = 1;
	int max_e = 4;
	std::srand(time(0));
	int effect = min_e + (std::rand() % (max_e - min_e + 1));
	
	switch (effect)
	{
	case 1:
		this->effect = SPEEDUP;
		break;
	case 2:
		this->effect = SPEEDDOWN;
		break;
	case 3:
		this->effect = PASSING;
		break;
	case 4:
		this->effect = INVERTED;
	}

	int min_d = 10;
	int max_d = 15;
	std::srand(time(0));
	int duration = min_d + (std::rand() % (max_d - min_d + 1));
	
	this->duration = duration;
	
	this->setPosition(Vector2{ (float)newRandomX * gridSize + (gridSize - getSize().x) / 2 , (float)newRandomY * gridSize + (gridSize - getSize().y) / 2});
}