/*******************************************************************************************
*
*   raylib game template
*
*   <Game title>
*   <Game description>
*
*   This game has been created using raylib (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2021 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "screens.h"    
#include <string>
#include <iostream>

 // NOTE: Declares global (extern) variables and screens functions

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Shared Variables Definition (global)
// NOTE: Those variables are shared between modules through screens.h
//----------------------------------------------------------------------------------
GameScreen currentScreen = TITLE;
Font font = { 0 };
Music music = { 0 };
Sound fxCoin = { 0 };
int screenWidth = 640;
int screenHeight = 360;
int gridSize = screenWidth / maxGridSizeWidth;
Resolution currentResolution = nHD;
std::string gameTitle = "SNAKE GAME";
float scale = (float) currentResolution / FHD * 2;

//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------


// Required variables to manage screen transitions (fade-in, fade-out)
static GameScreen transToScreen = UNKNOWN;

//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
static void UpdateDrawFrame(void);          // Update and draw one frame
static void ChangeToScreen(GameScreen screen);

//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //---------------------------------------------------------
    InitWindow(screenWidth, screenHeight, gameTitle.c_str());

    InitAudioDevice();      // Initialize audio device

    // Load global data (assets that must be available in all screens, i.e. font)
    font = LoadFont("resources/mecha.png");
    music = LoadMusicStream("resources/ambient.ogg");
    fxCoin = LoadSound("resources/coin.wav");

    SetMusicVolume(music, 1.0f);
    PlayMusicStream(music);

    // Setup and init first screen
    currentScreen = TITLE;

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);       // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (1)    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    // Unload current screen data before closing
    switch (currentScreen)
    {
        case TITLE: UnloadTitleScreen(); break;
        case OPTIONS: UnloadOptionsScreen(); break;
        case GAMEPLAY: UnloadGameplayScreen(); break;
        default: break;
    }

    // Unload global data loaded
    UnloadFont(font);
    UnloadMusicStream(music);
    UnloadSound(fxCoin);

    CloseAudioDevice();     // Close audio context

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

static void ChangeToScreen(GameScreen screen)
{
	// Unload current screen data
	switch (currentScreen)
	{
		case TITLE: UnloadTitleScreen(); break;
		case OPTIONS: UnloadOptionsScreen(); break;
		case GAMEPLAY: UnloadGameplayScreen(); break;
		default: break;
	}

	// Load next screen data
	switch (screen)
	{
		case TITLE: InitTitleScreen(); break;
		case OPTIONS: InitOptionsScreen(); break;
		case GAMEPLAY: InitGameplayScreen(); break;
		default: break;
	}

    currentScreen = screen;  // NOTE: currentScreen
}
// Update and draw game frame
static void UpdateDrawFrame(void)
{
    // Update
    //----------------------------------------------------------------------------------
    switch (currentScreen)
    {
        case TITLE: 
            UpdateTitleScreen();
            if (FinishTitleScreen() == GAMEPLAY) ChangeToScreen(GAMEPLAY);
            else if (FinishTitleScreen() == OPTIONS) ChangeToScreen(OPTIONS);
        break;
        case OPTIONS: 
            UpdateOptionsScreen();
            if (FinishOptionsScreen()) ChangeToScreen(TITLE);
        break;
        case GAMEPLAY: UpdateGameplayScreen(); 
            if (FinishGameplayScreen()) ChangeToScreen(TITLE);
        break;
    default:
        break;
    }

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(RAYWHITE);

        switch(currentScreen)
        {
            case TITLE: DrawTitleScreen(); break;
            case OPTIONS: DrawOptionsScreen(); break;
            case GAMEPLAY: DrawGameplayScreen(); break;
            default: break;
        }
		
        DrawFPS(10, 10);	
	EndDrawing();
	//----------------------------------------------------------------------------------
}