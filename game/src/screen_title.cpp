#include "raylib.h"
#include "screens.h"
#include <iostream>

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

enum selectedMenu { MENU_PLAY = 1, MENU_OPTIONS = 2, MENU_EXIT = 3};
enum selectedGameMode { MENU_CLASSIC = 1, MENU_ARCADE = 2 };
selectedMenu menuSelection = MENU_PLAY;
bool canSwitchMenu = true;
bool canSelectMenu = true;
bool showGameModeSelection = false;
selectedGameMode selectedGameModeMenu = MENU_CLASSIC;
GameMode gameMode;
//----------------------------------------------------------------------------------
// Title Screen Functions Definition
//----------------------------------------------------------------------------------

// Title Screen Initialization logic
void InitTitleScreen(void)
{
    // TODO: Initialize TITLE screen variables here!
    framesCounter = 0;
    finishScreen = 0;
    menuSelection = MENU_PLAY;
    canSwitchMenu = true;
}

// Title Screen Update logic
void UpdateTitleScreen(void)
{
    if ((IsKeyReleased(KEY_UP) || IsKeyReleased(KEY_W)) && !IsKeyDown(KEY_DOWN))
    {
        canSwitchMenu = true;
    }

    if ((IsKeyReleased(KEY_DOWN) || IsKeyReleased(KEY_S)) && !IsKeyDown(KEY_UP))
    {
        canSwitchMenu = true;
    }

    if (IsKeyReleased(KEY_ENTER) && !IsKeyDown(KEY_ENTER))
    {
        canSelectMenu = true;
    }
	
    if (canSwitchMenu)
    {    
        if (showGameModeSelection)
        {
            if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
            {
                PlaySound(menuEffect);
                canSwitchMenu = false;
                if (selectedGameModeMenu == MENU_CLASSIC)
                {
                    selectedGameModeMenu = MENU_ARCADE;
                }
                else
                {
                    selectedGameModeMenu = MENU_CLASSIC;
                }
            }
            if (canSelectMenu)
            {
                if (IsKeyDown(KEY_ENTER))
                {
                    PlaySound(menuEffect);
                    if (selectedGameModeMenu == MENU_CLASSIC)
                    {
                        gameMode = CLASSIC;
                    }
                    else if (selectedGameModeMenu == MENU_ARCADE)
                    {
                        gameMode = ARCADE;
                    }
                    else
                    {
                        gameMode = CLASSIC;
                    }

                    showGameModeSelection = false;
                    finishScreen = GAMEPLAY;
                }
            }
        }
        else
        {
            if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
            {
                PlaySound(menuEffect);
                canSwitchMenu = false;
                switch (menuSelection)
                {
                case MENU_PLAY:
                    menuSelection = MENU_OPTIONS;
                    break;
                case MENU_OPTIONS:
                    menuSelection = MENU_EXIT;
                    break;
                case MENU_EXIT:
                    menuSelection = MENU_PLAY;
                    break;
                default:
                    menuSelection = MENU_PLAY;
                    break;
                }
            }

            if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
            {
                PlaySound(menuEffect);
                canSwitchMenu = false;
                switch (menuSelection)
                {
                case MENU_PLAY:
                    menuSelection = MENU_EXIT;
                    break;
                case MENU_OPTIONS:
                    menuSelection = MENU_PLAY;
                    break;
                case MENU_EXIT:
                    menuSelection = MENU_OPTIONS;
                    break;
                default:
                    menuSelection = MENU_PLAY;
                    break;
                }
            }
		
            if (IsKeyPressed(KEY_ENTER))
            {
                PlaySound(menuEffect);
                canSelectMenu = false;
				
                switch (menuSelection)
                {
                case MENU_PLAY:
                    showGameModeSelection = true;
                    break;
                case MENU_OPTIONS:
                    finishScreen = OPTIONS;
                    break;
                case MENU_EXIT:
                    UnloadTitleScreen();

                    UnloadFont(font);
                    UnloadMusicStream(music);
                    UnloadSound(menuEffect);
					
                    CloseAudioDevice();

                    CloseWindow();
                    break;
                }
            }
        }
    }
}

// Title Screen Draw logic
void DrawTitleScreen(void)
{
    // TODO: Draw TITLE screen here!
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);

    Vector2 menupos{ GetScreenWidth() / 2, GetScreenHeight() / 2 };
    if (showGameModeSelection)
    {
		DrawText(title_gameModeText_1.c_str(),
            menupos.x - MeasureText(title_gameModeText_1.c_str(), 40 * scale) / 2, 
			menupos.y - 40 * scale, 
            40 * scale, 
            WHITE);
        DrawText(title_gameModeText_2.c_str(),
            menupos.x - MeasureText(title_gameModeText_2.c_str(), 40 * scale) / 2,
            menupos.y + 20 * scale,
            40 * scale,
            WHITE);
        DrawText(title_gameModeText_3.c_str(),
            menupos.x - MeasureText(title_gameModeText_3.c_str(), 40 * scale) / 2,
            menupos.y + 80 * scale,
            40 * scale,
            WHITE);

        switch (selectedGameModeMenu)
        {
        case MENU_CLASSIC:
            DrawRectangleLines(menupos.x - (MeasureText(title_gameModeText_2.c_str(), 40 * scale) + 20 * scale) / 2,
                menupos.y - 10 * scale + 20 * scale,
				MeasureText(title_gameModeText_2.c_str(), 40 * scale) + 20 * scale,
                40 * scale + 10 * scale,
				WHITE);
			break;
		case MENU_ARCADE:
            DrawRectangleLines(menupos.x - (MeasureText(title_gameModeText_3.c_str(), 40 * scale) + 20 * scale) / 2,
                menupos.y - 10 * scale + 80 * scale,
                MeasureText(title_gameModeText_2.c_str(), 40 * scale) + 20 * scale,
                40 * scale + 10 * scale,
                WHITE);
            break;
        default:
            DrawRectangleLines(menupos.x - (MeasureText(title_gameModeText_2.c_str(), 40 * scale) + 20 * scale) / 2,
                menupos.y - 10 * scale + 20 * scale,
                MeasureText(title_gameModeText_2.c_str(), 40 * scale) + 20 * scale,
                40 * scale + 10 * scale,
                WHITE);
        }
    }
    else
    {
        DrawText(gameTitle.c_str(), menupos.x - MeasureText(gameTitle.c_str(), 70 * scale) / 2, menupos.y - 160 * scale, 70 * scale, GREEN);
        DrawText("PLAY", menupos.x - MeasureText("PLAY", 40 * scale) / 2, menupos.y - 40 * scale, 40 * scale, WHITE);
        DrawText("OPTIONS", menupos.x - MeasureText("OPTIONS", 40 * scale) / 2, menupos.y + 20 * scale, 40 * scale, WHITE);
        DrawText("EXIT", menupos.x - MeasureText("EXIT", 40 * scale) / 2, menupos.y + 80 * scale, 40 * scale, WHITE);

        switch (menuSelection)
        {
        case MENU_PLAY:
            DrawRectangleLines(menupos.x - (MeasureText("PLAY", 40 * scale) + 20 * scale) / 2,
                menupos.y - 10 * scale - 40 * scale, 
                MeasureText("PLAY", 40 * scale) + 20 * scale, 
                40 * scale + 10 * scale, WHITE);
            break;
        case MENU_OPTIONS:
            DrawRectangleLines(menupos.x - (MeasureText("OPTIONS", 40 * scale) + 20 * scale) / 2, menupos.y - 10 * scale + 20 * scale, MeasureText("OPTIONS", 40 * scale) + 20 * scale, 40 * scale + 10 * scale, WHITE);
            break;
        case MENU_EXIT:
            DrawRectangleLines(menupos.x - (MeasureText("EXIT", 40 * scale) + 20 * scale) / 2, menupos.y - 10 * scale + 80 * scale, MeasureText("EXIT", 40 * scale) + 20 * scale, 40 * scale + 10 * scale, WHITE);
            break;
        default:
            DrawRectangleLines(menupos.x - (MeasureText("PLAY", 40 * scale) + 20 * scale) / 2, menupos.y - 10 * scale - 40 * scale, MeasureText("PLAY", 40 * scale) + 20 * scale, 40 * scale + 10 * scale, WHITE);
        }
    }
    

}


// Title Screen Unload logic
void UnloadTitleScreen(void)
{
    // TODO: Unload TITLE screen variables here!
}

// Title Screen should finish?
int FinishTitleScreen(void)
{
    return finishScreen;
}