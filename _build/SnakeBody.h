#pragma once

#include <raylib.h>

class SnakeBody {
	Vector2 size = { 0, 0 };
	Vector2 position = { 0, 0 };
	Color color = { 0, 0, 0, 0 };
	Color colorFrame = { 0, 0, 0, 0 };
public:
	SnakeBody();
	SnakeBody(Vector2, Vector2 , Color, Color);
	void Draw();
	void Update(int , Vector2 );
	void Move(Vector2 );

	void setPositon(Vector2 );
	void setSize(Vector2 );
	void setColor(Color );
	void setColorFrame(Color);

	Vector2 getPosition();
	Vector2 getSize();
	Color getColor();
	Color getColorFrame();
};