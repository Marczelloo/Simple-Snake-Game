#include "raylib.h"
#include "screens.h"
#include "SnakeHead.h"
#include "Fruit.h"
#include "SpecialFruit.h"
#include <iostream>
#include <vector>
#include "Strings.h"

//add scalability for all resolution for gameplay

enum State { START, PLAYING, PAUSED, LOST};

static int framesCounter = 0;
static int finishScreen = 0;
int score;
State gameState = START;

SnakeHead player;
std::vector<SnakeBody> playerBody(1);
Fruit fruit;
SpecialFruit specialFruit;

void InitGameplayScreen(void)
{
	framesCounter = 0;
	finishScreen = 0;
	gameState = START;
	score = 0;
	player = SnakeHead(Vector2{ 10, 10 }, Vector2{ 1, 1 }, GREEN, DARKGREEN, RIGHT, 1);
	std::vector<SnakeBody> newPlayerBody(1);
	playerBody = newPlayerBody;
	playerBody[0] = SnakeBody(Vector2{ 10, 10}, Vector2{ 1, 1 }, GREEN, DARKGREEN);
	fruit = Fruit(Vector2{0, 0}, Vector2{ .8, .8 }, RED);
	specialFruit = SpecialFruit();
	specialFruit.setSize(fruit.getSize());
	specialFruit.setColor(BLUE);
	fruit.SpawnNew(player.getPosition(), playerBody.data(), playerBody.size());

	if (gameMode == ARCADE)
	{
		specialFruit.SpawnNew(player.getPosition(), playerBody.data(), playerBody.size(), fruit);
	}
}

void UpdateGameplayScreen(void)
{
	framesCounter++;

	if (gameState == START)
	{
		if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
		{
			gameState = PLAYING;
		}
	}

	if (gameState == PLAYING)
	{
		if (IsKeyPressed(KEY_P))
		{
			gameState = PAUSED;
		}

		int const size = playerBody.size();

		if (framesCounter % player.getFrameSpeed() == 0)
		{
			for (int i = size - 1; i > 0; i--)
			{
				playerBody[i].Update(framesCounter, playerBody[i - 1].getPosition());
			}
			playerBody[0].Update(framesCounter, player.getPosition());
		}
	
		player.Update(framesCounter);

		if (player.CheckCollisionWithBarriers()) gameState = LOST;
		if (player.CheckCollisionWithBody(playerBody.data(), playerBody.size())) gameState = LOST;
		if (player.CheckCollisionWithFruit(fruit))
		{
			SnakeBody newSnakeBody = SnakeBody(playerBody[size - 1].getPosition(), Vector2{ 1, 1 }, player.getColor(), player.getColorFrame());
			playerBody.push_back(newSnakeBody);
			
			fruit.SpawnNew(player.getPosition(), playerBody.data(), playerBody.size());

			if (gameMode == ARCADE)
			{
				if (!specialFruit.getActive())
				{
					specialFruit.SpawnNew(player.getPosition(), playerBody.data(), playerBody.size(), fruit);
				}	
			}
			
			score += 100;
		}

		if (gameMode == ARCADE)
		{
			if (player.CheckCollisionWithSpecialFruit(specialFruit))
			{
				if (specialFruit.getActive())
				{
					player.addEffect(specialFruit.getEffect(), specialFruit.getDuration());

					specialFruit.setActive(false);

					SnakeBody newSnakeBody = SnakeBody(playerBody[size - 1].getPosition(), Vector2{ 1, 1 }, player.getColor(), player.getColorFrame());
					playerBody.push_back(newSnakeBody);

					score += 100;
				}
			}

			player.UpdateEffectDuration();
		}
	}	

	if (gameState == PAUSED)
	{
		if (IsKeyPressed(KEY_SPACE)) gameState = PLAYING;
		if (IsKeyPressed(KEY_ESCAPE)) finishScreen = TITLE;
	}

	if (gameState == LOST)
	{
		if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER))
		{
			InitGameplayScreen();
		}

		if (IsKeyPressed(KEY_ESCAPE))
		{
			finishScreen = TITLE;
		}
	}
 }

void DrawGameplayScreen(void)
{
	ClearBackground(BLACK);
	
	if (gameState == START)
	{
		DrawText(gameplay_startText_1.c_str(), 
			GetScreenWidth() / 2 - MeasureText(gameplay_startText_1.c_str(), 40 * scale) / 2, 
			GetScreenHeight() / 2 - 20 * scale,
			40 * scale, 
			WHITE);
		DrawText(gameplay_startText_2.c_str(), 
			GetScreenWidth() / 2 - MeasureText(gameplay_startText_2.c_str(), 40 * scale) / 2,
			GetScreenHeight() / 2 + 20 * scale, 
			40 * scale, 
			WHITE);
	}
	
	if (gameState == PLAYING)
	{
		for each (SnakeBody sb in playerBody)
		{
			sb.Draw();
		}
		playerBody[0].Draw();
		player.Draw();
		fruit.Draw();
		DrawGameplayHUD();

		if (gameMode == ARCADE)
		{
			specialFruit.Draw();
			player.DrawEffects();
		}
	}

	if (gameState == PAUSED)
	{
		DrawRectangle(screenWidth / 2 - screenWidth / 4,
			screenHeight / 2 - screenHeight / 4,
			screenWidth / 2,
			screenHeight / 2,
			BLACK);
		DrawRectangleLinesEx({ (float)screenWidth / 2 - screenWidth / 4,
			(float)screenHeight / 2 - screenHeight / 4,
			(float)screenWidth / 2,
			(float)screenHeight / 2 },
			.25 * gridSize,
			WHITE);
		DrawText(gameplay_pausedText_1.c_str(), screenWidth / 2 - MeasureText(gameplay_pausedText_1.c_str(), 40 * scale) / 2, screenHeight / 2 - 80 * scale, 40 * scale, WHITE);
		DrawText(gameplay_pausedText_2.c_str(), screenWidth / 2 - MeasureText(gameplay_pausedText_2.c_str(), 30 * scale) / 2, screenHeight / 2, 30 * scale, WHITE);
		DrawText(gameplay_pausedText_3.c_str(), screenWidth / 2 - MeasureText(gameplay_pausedText_3.c_str(), 30 * scale) / 2, screenHeight / 2 + 80 * scale, 30 * scale, WHITE);
	}


	if (gameState == LOST)
	{
		DrawText(gameplay_lostText_3.c_str(),
			GetScreenWidth() / 2 - MeasureText(gameplay_lostText_3.c_str(), 40 * scale) / 2,
			GetScreenHeight() / 2 - 40 * scale,
			40 * scale,
			RED);
		DrawText(gameplay_lostText_1.c_str(),
			GetScreenWidth() / 2 - MeasureText(gameplay_lostText_1.c_str(), 40 * scale) / 2,
			GetScreenHeight() / 2,
			40 * scale,
			WHITE
		);
		DrawText(gameplay_lostText_2.c_str(),
			GetScreenWidth() / 2 - MeasureText(gameplay_lostText_2.c_str(), 40 * scale) / 2,
			GetScreenHeight() / 2 + 40 * scale,
			40 * scale,
			WHITE
		);
	}
}

void DrawGameplayHUD(void)
{
	DrawText(TextFormat(gameplay_scoreText.c_str(), score),
		screenWidth - MeasureText(TextFormat(gameplay_scoreText.c_str(), score), 40 * scale) - 20,
		10,
		40 * scale,
		WHITE
	);
}

void UnloadGameplayScreen(void)
{

}

int FinishGameplayScreen(void)
{
	return finishScreen;
}