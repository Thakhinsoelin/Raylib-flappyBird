#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "../../rgui/examples/styles/style_cyber.h"
#include <time.h>

#define RRES_IMPLEMENTATION
#include "../../rres/src/rres.h"

#define RRES_RAYLIB_IMPLEMENTATION
#include "../../rres/src/rres-raylib.h"

#define MAX_BIRD_SPEED     15
#define MIN_BIRD_SPEED      1

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 640

#define BACK_WIDTH 640
#define BACK_HEIGHT 640

struct Tile {
    Vector2 pos;
    Vector2 size;
    Texture tile_t;
};

Texture2D loadImageWithTexture(Texture textureToChange, Image image) {
    
    
    UnloadTexture(textureToChange);
    
    return LoadTextureFromImage(image);

}

//Draw a part of a texture (defined by a rectangle) with 'pro' parameters 
//NOTE: This scale the texture based on the source given. Not the entire texture
//NOTE: origin is relative to destination rectangle size
void DrawTextureRecEx(Texture2D texture, Rectangle source, Vector2 position, float rotation, float scale, Color tint) {
    
    Rectangle dest = { position.x, position.y, (float)source.width*scale, (float)source.height*scale };
    Vector2 origin = { 0.0f, 0.0f };

    DrawTexturePro(texture, source, dest, origin, rotation, tint);
}

int main(int argc, char** argv) {
    Vector2 anchor01 = {100,100};
    bool styleGuard = true;
    bool ControlWindow = true;

    int back_counter = 0;

    float bird_scale = 4;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Flappy Bird");
    SetTargetFPS(60);
    Texture2D backgrounds[5] = {0};
    backgrounds[0] = LoadTexture("resources/Background/Background1.png");
    backgrounds[1] = LoadTexture("resources/Background/Background2.png");
    backgrounds[2] = LoadTexture("resources/Background/Background3.png");
    backgrounds[3] = LoadTexture("resources/Background/Background4.png");
    backgrounds[4] = LoadTexture("resources/Background/Background5.png");

    Texture testTexture = {};

    rresCentralDir dir = rresLoadCentralDirectory("resources/background.rres");

    int idTex = rresGetResourceId(dir, "Background1.png");

    rresResourceChunk chunkTex = rresLoadResourceChunk("resources/background.rres", idTex);

    {
        Image img = LoadImageFromResource(chunkTex);
        testTexture = LoadTextureFromImage(img);
        UnloadImage(img);
    }

    rresUnloadResourceChunk(chunkTex);
    rresUnloadCentralDirectory(dir);


    Texture2D birds[2] = {0};
    birds[0] = LoadTexture("resources/Player/StyleBird1/AllBird1.png");

    birds[1] = LoadTexture("resources/Player/StyleBird2/AllBird2.png");

    int currentBird = 0;

    Vector2 bird_pos = { 250, 250};
    Rectangle birdRec = { 0.0f, 0.0f, (float)birds[0].width/4, (float)birds[0].height/7 };
    int currentFrame = 0;
    int currentBirdRow = 0;
    int framesCounter = 0;
    float framesSpeed = 6;            // Number of spritesheet frames shown by second
    
    
    Texture2D background_t = backgrounds[4];
    
    int frame = 0;

    int ani_frames = 4;
    

    int x1 = 0;
    int x2 = BACK_WIDTH;

    

    while (!WindowShouldClose())
    {
        if(styleGuard) {
            GuiLoadStyleDefault();
            GuiLoadStyleCyber();
            styleGuard = false;
        }
        framesCounter++;
        float deltaTime = GetFrameTime();

        if (framesCounter >= (60/framesSpeed))
        {
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > 5) currentFrame = 0;

            birdRec.x = (float)currentFrame*(float)birds[0].width/4;
            birdRec.y = (float)currentBirdRow*(float)birds[0].height/7;
        }

        if (framesSpeed > MAX_BIRD_SPEED) framesSpeed = MAX_BIRD_SPEED;
        else if (framesSpeed < MIN_BIRD_SPEED) framesSpeed = MIN_BIRD_SPEED;

        if (IsKeyPressed(KEY_SPACE))
        {
            printf("Space is pressed");
        } else if (IsKeyPressed(KEY_ENTER)) {
            back_counter++;
            if (back_counter >= 5)
            {
                back_counter = 0;
            }
            
        }

        frame++;
        if(frame/4 >= ani_frames) {
            frame= 0;
        }

        
        BeginDrawing();
            if(x1 <= -BACK_WIDTH) x1 = BACK_WIDTH;
            if(x2 <= -BACK_WIDTH) x2 = BACK_WIDTH; 
            // DrawTexture(background_t, x1, 0, WHITE);
            // DrawTexture(background_t, x2, 0, WHITE);

            DrawTextureEx(backgrounds[back_counter], {(float)x1, 0}, 0, 2.5, WHITE);
            DrawTextureEx(backgrounds[back_counter], {(float)x2, 0}, 0, 2.5, WHITE);

            
            if (ControlWindow)
            {
                ControlWindow = !GuiWindowBox({ anchor01.x + 0, anchor01.y + 0, 296, 192 }, "SAMPLE TEXT");
                GuiSliderBar({ anchor01.x + 144, anchor01.y + 40, 152, 16 }, "Bird Size", NULL, &bird_scale, 1, 8);
                GuiSliderBar({ anchor01.x + 144, anchor01.y + 64, 152, 16 }, "Bird Animation Speed", NULL, &framesSpeed, 0, 8);
                if (GuiButton({ anchor01.x + 144, anchor01.y + 88, 152, 24 }, "Change Background")) {
                    back_counter++;
                    if (back_counter >= 5)
                    {
                        back_counter = 0;
                    }
                }; 
                if (GuiButton({ anchor01.x + 144, anchor01.y + 120, 152, 24 }, "Change Bird")) {
                    currentBirdRow++;
                    if (currentBirdRow >= 7)
                    {
                        currentBirdRow = 0;
                    }
                }; 
                if (GuiButton({ anchor01.x + 144, anchor01.y + 152, 152, 24 }, "Change Entire Bird Sprite")) {
                    currentBird++;
                    if (currentBird > 1 )
                    {
                        currentBird = 0;
                    }
                }; 
            }

            //Drawing controls
            // GuiSliderBar({330, 330, 100, 50}, "Bird_size", NULL, &bird_scale, 1, 7);
            // GuiSliderBar({330, 390, 100, 50}, "Bird Animation Speed", NULL, &framesSpeed, 1, 8);
            // if (GuiLabelButton({330, 450, 60, 20}, "Change Background")) {
            //     back_counter++;
            //     if (back_counter >= 5)
            //     {
            //         back_counter = 0;
            //     }
            // };

            // if (GuiLabelButton({330, 475, 60, 20}, "Change Bird")) {
            //     currentBirdRow++;
            //     if (currentBirdRow >= 7)
            //     {
            //         currentBirdRow = 0;
            //     }
            // };

            

            // if (GuiLabelButton({330, 500, 60, 20}, "Change Entire Bird Sprite")) {
            //     currentBird++;
            //     if (currentBird > 1 )
            //     {
            //         currentBird = 0;
            //     }
            // };

            DrawTextureRecEx(birds[currentBird], birdRec, bird_pos, 0, bird_scale, WHITE);
            

        EndDrawing();
        x1--;
        x2--;
    }
    UnloadTexture(testTexture);
    CloseWindow();
    return 0;
}