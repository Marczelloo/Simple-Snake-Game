/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Screens Functions Declarations (Init, Update, Draw, Unload)
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#include <string>
#ifndef SCREENS_H
#define SCREENS_H


//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
typedef enum GameScreen { UNKNOWN = -1, LOGO = 0, TITLE, OPTIONS, GAMEPLAY, ENDING, EXIT } GameScreen;
typedef enum Resolution { nHD = 1, HD = 2, HDP = 3, FHD = 4 } Resolution;
typedef enum GameMode { CLASSIC = 1, ARCADE = 2 } GameMode;

//----------------------------------------------------------------------------------
// Global Variables Declaration (shared by several modules)
//----------------------------------------------------------------------------------
extern GameScreen currentScreen;
extern Font font;
extern Music music;
extern Sound fxCoin;
extern std::string gameTitle;
extern int screenWidth;
extern int screenHeight;
extern float scale;
extern Resolution currentResolution;
static int maxGridSizeWidth = 32;
static int maxGridSizeHeight = 18;
extern int gridSize;
extern GameMode gameMode;

static const std::string title_gameModeText_1 = "CHOOSE GAME MODE";
static const std::string title_gameModeText_2 = "CLASSIC";
static const std::string title_gameModeText_3 = "ARCADE";

#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

//----------------------------------------------------------------------------------
// Title Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitTitleScreen(void);
void UpdateTitleScreen(void);
void DrawTitleScreen(void);
void UnloadTitleScreen(void);
int FinishTitleScreen(void);


// Options Screen Functions Declaration
void InitOptionsScreen(void);
void UpdateOptionsScreen(void);
void DrawOptionsScreen(void);
void UnloadOptionsScreen(void);
int FinishOptionsScreen(void);
void OptionsManageResolutionChange(int);


// Gameplay Screen Functions Declaration
void InitGameplayScreen(void);
void UpdateGameplayScreen(void);
void DrawGameplayScreen(void);
void DrawGameplayHUD(void);
void UnloadGameplayScreen(void);
int FinishGameplayScreen(void);


#ifdef __cplusplus
}
#endif

#endif // SCREENS_H