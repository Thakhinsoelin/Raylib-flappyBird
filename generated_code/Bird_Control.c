/*******************************************************************************************
*
*   LayoutName v1.0.0 - Tool Description
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 raylib technologies. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#include "raylib.h"
#include <stdbool.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "../rgui/styles/cyber/style_cyber.h"
//----------------------------------------------------------------------------------
// Controls Functions Declaration
//----------------------------------------------------------------------------------
static void BackgroundChange();
static void Bird();
static void Bird();

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //---------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    bool isStyleActive = true;
    int prevStyle = 3;

    InitWindow(screenWidth, screenHeight, "layout_name");

    // layout_name: controls initialization
    //----------------------------------------------------------------------------------
    Vector2 anchor01 = { 120, 72 };
    
    bool ControlWindow = true;
    float Bird_SizeValue = 0.0f;
    float Bird_Ani_SpeedValue = 0.0f;
    //----------------------------------------------------------------------------------
    bool exitWindow = false;
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!exitWindow)    // Detect window close button or ESC key
    {
        exitWindow = WindowShouldClose();
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Implement required update logic
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        
        if(isStyleActive) {
            GuiLoadStyleDefault();
            GuiLoadStyleCyber();

            isStyleActive = false;
        }

        BeginDrawing();

            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR))); 

            // raygui: controls drawing
            //----------------------------------------------------------------------------------
            if (ControlWindow)
            {
                ControlWindow = !GuiWindowBox((Rectangle){ anchor01.x + 0, anchor01.y + 0, 296, 192 }, "SAMPLE TEXT");
                GuiSliderBar((Rectangle){ anchor01.x + 144, anchor01.y + 40, 152, 16 }, "Bird Size", NULL, &Bird_SizeValue, 0, 100);
                GuiSliderBar((Rectangle){ anchor01.x + 144, anchor01.y + 64, 152, 16 }, "Bird Animation Speed", NULL, &Bird_Ani_SpeedValue, 0, 100);
                if (GuiButton((Rectangle){ anchor01.x + 144, anchor01.y + 88, 152, 24 }, "Change Background")) BackgroundChange(); 
                if (GuiButton((Rectangle){ anchor01.x + 144, anchor01.y + 120, 152, 24 }, "Change Bird")) Bird(); 
                if (GuiButton((Rectangle){ anchor01.x + 144, anchor01.y + 152, 152, 24 }, "Change Entire Bird Sprite")) Bird(); 
            }
            //----------------------------------------------------------------------------------

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//------------------------------------------------------------------------------------
// Controls Functions Definitions (local)
//------------------------------------------------------------------------------------
static void BackgroundChange()
{
    // TODO: Implement control logic
}
static void Bird()
{
    // TODO: Implement control logic
}

