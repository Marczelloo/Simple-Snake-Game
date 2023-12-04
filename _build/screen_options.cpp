#include "raylib.h"
#include "screens.h"
#include <iostream>
#include <string>

static int framesCounter = 0;
static int finishScreen = 0;


enum selectedMenu { OPTIONS_RESOLUTION = 1, OPTIONS_VOLUME = 2, OPTIONS_GOBACK = 3, OPTIONS_FULLSCREEN = 4 };

selectedMenu optionsMenuSelection;
bool optionsCanSwitchMenu;

int selectedVolume;
bool optionCanSwitchVolume;

std::string displayResolution;

void InitOptionsScreen(void)
{
	framesCounter = 0;
    finishScreen = 0;
	optionsCanSwitchMenu = true;
	optionsMenuSelection = OPTIONS_RESOLUTION;
    switch(screenWidth)
    {
        case 640:
            currentResolution = nHD;
            displayResolution = "640 x 360";
            scale = (float)currentResolution / FHD * 2;	
            gridSize = screenWidth / maxGridSizeWidth;
        break;
        case 1280:
            currentResolution = HD;
            displayResolution = "1280 x 720";
            scale = (float)currentResolution / FHD * 2;
            gridSize = screenWidth / maxGridSizeWidth;
        break;
        case 1600:
            currentResolution = HDP;
            displayResolution = "1600 x 900";
            scale = (float)currentResolution / FHD;
            gridSize = screenWidth / maxGridSizeWidth;
        break;
        case 1920:
            currentResolution = FHD;
            displayResolution = "1920 x 1080";
            scale = (float)currentResolution / FHD;
            gridSize = screenWidth / maxGridSizeWidth;
        break;
    }
    scale = (float)currentResolution / FHD * 2;
    
    selectedVolume = GetMasterVolume() * 10;
    optionCanSwitchVolume = true;
}

void UpdateOptionsScreen(void)
{
    if (optionsCanSwitchMenu)
    {
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
        {
            PlaySound(menuEffect);
            optionsCanSwitchMenu = false;
            switch (optionsMenuSelection)
            {
            case OPTIONS_RESOLUTION:
                optionsMenuSelection = OPTIONS_FULLSCREEN;
                break;
            case OPTIONS_FULLSCREEN:
                optionsMenuSelection = OPTIONS_VOLUME;
            break;
            case OPTIONS_VOLUME:
                optionsMenuSelection = OPTIONS_GOBACK;
                break;
            case OPTIONS_GOBACK:
                optionsMenuSelection = OPTIONS_RESOLUTION;
                break;
            default:
                optionsMenuSelection = OPTIONS_RESOLUTION;
                break;
            }
        }

        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
        {
            PlaySound(menuEffect);
            optionsCanSwitchMenu = false;
            switch (optionsMenuSelection)
            {
            case OPTIONS_RESOLUTION:
                optionsMenuSelection = OPTIONS_GOBACK;
                break;
            case OPTIONS_FULLSCREEN:
                optionsMenuSelection = OPTIONS_RESOLUTION;
            break;
            case OPTIONS_VOLUME:
                optionsMenuSelection = OPTIONS_FULLSCREEN;
                break;
            case OPTIONS_GOBACK:
                optionsMenuSelection = OPTIONS_VOLUME;
                break;
            default:
                optionsMenuSelection = OPTIONS_RESOLUTION;
                break;
            }
        }
    }

    if ((IsKeyReleased(KEY_UP) || IsKeyReleased(KEY_W)) && !IsKeyDown(KEY_DOWN))
    {
        optionsCanSwitchMenu = true;
    }

    if ((IsKeyReleased(KEY_DOWN) || IsKeyReleased(KEY_S)) && !IsKeyDown(KEY_UP))
    {
        optionsCanSwitchMenu = true;
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        PlaySound(menuEffect);
        if (optionsMenuSelection == OPTIONS_GOBACK)
        {
            finishScreen = TITLE;
        }
		
        if (optionsMenuSelection == OPTIONS_FULLSCREEN)
        {
            ToggleFullscreen();
        }
    }

    if (optionsMenuSelection == OPTIONS_RESOLUTION)
    {
        if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
        {
            PlaySound(menuEffect);
            OptionsManageResolutionChange(0);
        }
        else if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
        {
            PlaySound(menuEffect);
            OptionsManageResolutionChange(1);
        }
    }

    HandleVolumeChange();
}

void HandleVolumeChange()
{
	if(IsKeyReleased(KEY_LEFT) || IsKeyReleased(KEY_A) && !IsKeyPressed(KEY_RIGHT) && !IsKeyPressed(KEY_D)) optionCanSwitchVolume = true;
    if (IsKeyReleased(KEY_RIGHT) || IsKeyReleased(KEY_D) && !IsKeyPressed(KEY_LEFT) && !IsKeyPressed(KEY_A)) optionCanSwitchVolume = true;
		
    if (optionsMenuSelection == OPTIONS_VOLUME)
    {
        if (optionCanSwitchVolume)
        {
            if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
            {
                PlaySound(menuEffect);
                optionCanSwitchVolume = false;
                if (selectedVolume == 0) return;
                selectedVolume--;
                SetMasterVolume((float)selectedVolume / 10);
            }

            if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
            {
                PlaySound(menuEffect);
                optionCanSwitchVolume = false;
                if (selectedVolume == 10) return;
                selectedVolume++;
                SetMasterVolume((float)selectedVolume / 10);
            }
        }
    }
}

void DrawOptionsScreen(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);

    scale = (float)currentResolution / FHD * 2;

    Vector2 menuPos = { GetScreenWidth() / 2, GetScreenHeight() / 2 };
    DrawText(("RESOLUTION:  " + displayResolution).c_str(),
        menuPos.x - MeasureText(("RESOLUTION:  " + displayResolution).c_str(), 40 * scale) / 2,
        menuPos.y - 60 * scale,
        40 * scale,
        WHITE);
    DrawText("FULLSCREEN: ",
        menuPos.x - MeasureText("FULLSCREEN: ", 40 * scale) / 2,
        menuPos.y,
        40 * scale,
        WHITE);
    DrawText(("VOLUME: " + std::to_string(selectedVolume)).c_str(),
        menuPos.x - MeasureText(("VOLUME: " + std::to_string(selectedVolume)).c_str(), 40 * scale) / 2,
        menuPos.y + 60 * scale,
        40 * scale,
        WHITE);
    DrawText("GO BACK",
        menuPos.x - MeasureText("GO BACK", 40 * scale) / 2,
        menuPos.y + 120 * scale,
        40 * scale,
        WHITE);

    switch (optionsMenuSelection)
    {
    case OPTIONS_RESOLUTION:
        DrawRectangleLines(menuPos.x - (MeasureText(("RESOLUTION:  " + displayResolution).c_str(), 40 * scale) + 20) / 2, menuPos.y - 10 * scale - 60 * scale, MeasureText(("RESOLUTION:  " + displayResolution).c_str(), 40 * scale) + 20, 40 * scale + 10 * scale, WHITE);
        break;
    case OPTIONS_FULLSCREEN:
        DrawRectangleLines(menuPos.x - (MeasureText("FULLSCREEN: ", 40 * scale) + 20) / 2, menuPos.y - 10 * scale, MeasureText("FULLSCREEN", 40 * scale) + 20, 40 * scale + 10 * scale, WHITE);
        break;
    case OPTIONS_VOLUME:
        DrawRectangleLines(menuPos.x - (MeasureText(("VOLUME: " + std::to_string(selectedVolume)).c_str(), 40 * scale) + 20) / 2, menuPos.y - 10 * scale + 60 * scale, MeasureText(("VOLUME: " + std::to_string(selectedVolume)).c_str(), 40 * scale) + 20, 40 * scale + 10 * scale, WHITE);
        break;
    case OPTIONS_GOBACK:
        DrawRectangleLines(menuPos.x - (MeasureText("GO BACK", 40 * scale) + 20) / 2, menuPos.y - 10 * scale + 120 * scale, MeasureText("GO BACK", 40 * scale) + 20, 40 * scale + 10 * scale, WHITE);
        break;
    default:
        DrawRectangleLines(menuPos.x - 240 * scale / 2, menuPos.y - 60 * scale, 240 * scale, 40 * scale, WHITE);
    }
}

void UnloadOptionsScreen(void)
{

}

int FinishOptionsScreen(void)
{
	return finishScreen;
}

void OptionsManageResolutionChange(int direction)
{
    if (direction)
    {
        switch (currentResolution)
        {
			case nHD:
                currentResolution = HD;
			break;
			case HD:
                currentResolution = HDP;
			break;
			case HDP:
                currentResolution = FHD;
			break;
			case FHD:
                currentResolution = nHD;
			break;
			default:
                currentResolution = FHD;
			break;
		}
	}
	else
	{
		switch (currentResolution)
		{
		case nHD:
            currentResolution = FHD;
		break;
		case HD:
            currentResolution = nHD;
		break;
		case HDP:
            currentResolution = HD;
		break;
		case FHD:
            currentResolution = HDP;
		break;
		default:
            currentResolution = FHD;
		break;
		}
	}

    switch (currentResolution)
    {
        case nHD:
            displayResolution = "640 x 360";
            screenWidth = 640;
            screenHeight = 360;
            scale = (float)currentResolution / FHD * 2;
            gridSize = screenWidth / maxGridSizeWidth;
        break;
        case HD:
			displayResolution = "1280 x 720";
            screenWidth = 1280;
            screenHeight = 720;
            scale = (float)currentResolution / FHD * 2;
            gridSize = screenWidth / maxGridSizeWidth;

		break;
		case HDP:
			displayResolution = "1600 x 900";
            screenWidth = 1600;
            screenHeight = 900;
            scale = (float)currentResolution / FHD;
            gridSize = screenWidth / maxGridSizeWidth;
		break;
		case FHD:
			displayResolution = "1920 x 1080";
            screenWidth = 1920;
            screenHeight = 1080;
            scale = (float)currentResolution / FHD;	
            gridSize = screenWidth / maxGridSizeWidth;
		break;
		default:
			displayResolution = "1920 x 1080";
            screenWidth = 1920;
            screenHeight = 1080;
            scale = (float)currentResolution / FHD;
            gridSize = screenWidth / maxGridSizeWidth;
		break;
	}

    SetWindowSize(screenWidth, screenHeight);
    SetWindowPosition(screenWidth / 2 - GetScreenWidth() / 2, screenHeight / 2 - GetScreenHeight() / 2);    
}
 