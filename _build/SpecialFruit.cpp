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
	this->active = false;
}

SpecialFruit::SpecialFruit(Vector2 pos, Vector2 size, Color color, float durtation, Effect effect) : Fruit(pos, size, color)
{
	this->duration = durtation;
	this->effect = effect;
	this->active = false;
}

float SpecialFruit::getDuration()
{
	return duration;
}

Effect SpecialFruit::getEffect()
{
	return effect;
}

bool SpecialFruit::getActive()
{
	return active;
}

void SpecialFruit::setActive(bool active)
{
	this->active = active;
}

void SpecialFruit::SpawnNew(Vector2 snakehead, SnakeBody* snakebody, int snakeBodySize, Fruit fruit)
{	
	active = false;
	int min = 1;
	int max = 100;
	std::srand(std::time(0));
	int chance = min + (std::rand() % (max - min + 1));
	
	if (chance < 50) return;
	
	Vector2 fruitVec { fruit.getPosition().x, fruit.getPosition().y };
	fruitVec.x = fruitVec.x - (gridSize - fruit.getSize().x) / 2;
	fruitVec.y = fruitVec.y - (gridSize - fruit.getSize().y) / 2;

	active = true;
	
	srand(time(0));
	int minRange = 0;
	int maxRangeX = maxGridSizeWidth;
	int maxRangeY = maxGridSizeHeight;

	int newRandomX = rand() % (maxRangeX - minRange) + minRange;
	int newRandomY = rand() % (maxRangeY - minRange) + minRange;

	
	if (newRandomX == snakehead.x)
	{
		while (newRandomX = snakehead.x)
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

	if (newRandomX * gridSize == fruitVec.x)
	{
		std::cout << "test x" << std::endl;
		do
		{
			newRandomX = rand() % (maxRangeX - minRange) + minRange;
		} 
		while (newRandomX * gridSize == fruitVec.x);
	}
	
	if (newRandomY * gridSize == fruitVec.y)
	{
		do
		{
			newRandomY = rand() % (maxRangeY - minRange) + minRange;
		} 
		while (newRandomY * gridSize == fruitVec.y);
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

	std::cout << "special: " << newRandomX * gridSize << " " << newRandomY * gridSize << std::endl;
	
	this->setPosition(Vector2{ (float)newRandomX * gridSize + (gridSize - getSize().x) / 2 , (float)newRandomY * gridSize + (gridSize - getSize().y) / 2});
}

void SpecialFruit::Draw()
{
	if (active)
	{
		DrawRectangle(getPosition().x, 
			getPosition().y, 
			getSize().x, 
			getSize().y, 
			getColor());
	}
}