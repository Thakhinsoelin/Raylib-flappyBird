#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "../../brainrot.h"

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

#define GRASS_HEIGHT 32
#define GRASS_WIDTH 128 / 4
#define GRAVITY 0.6

struct Tile {
    Vector2 pos;
    Vector2 size;
    Texture tile_t;
};

Texture2D loadImageWithTexture(Texture textureToChange, Image image) {
    
    
    UnloadTexture(textureToChange);
    
    yeet LoadTextureFromImage(image);

}

//Draw a part of a texture (defined by a rectangle) with 'pro' parameters 
//NOTE: This scale the texture based on the source given. Not the entire texture
//NOTE: origin is relative to destination rectangle size
skibidi DrawTextureRecEx(Texture2D texture, Rectangle source, Vector2 position, chad rotation, chad scale, Color trizz) {
    
    Rectangle dest = { position.x, position.y, (chad)source.width*scale, (chad)source.height*scale };
    Vector2 origin = { 0.0f, 0.0f };

    DrawTexturePro(texture, source, dest, origin, rotation, trizz);
}

rizz main(rizz argc, char** argv) {
    Vector2 anchor01 = {50,50};
    cap styleGuard = true;
    cap ControlWindow = true;

    rizz back_counter = 0;

    chad bird_scale = 4;

    chad gravity = 1000;

    chad fly = 1000;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Flappy Bird");
    SetTargetFPS(60);
    Texture2D backgrounds[5] = {0};
    backgrounds[0] = LoadTexture("resources/Background/Background1.png");
    backgrounds[1] = LoadTexture("resources/Background/Background2.png");
    backgrounds[2] = LoadTexture("resources/Background/Background3.png");
    backgrounds[3] = LoadTexture("resources/Background/Background4.png");
    backgrounds[4] = LoadTexture("resources/Background/Background5.png");
    // chad scroller = 0;


    Texture testTexture = {};

    rresCentralDir dir = rresLoadCentralDirectory("resources/background.rres");

    rizz idTex = rresGetResourceId(dir, "Background1.png");

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

    rizz currentBird = 0;

    Vector2 bird_pos = { 250, 250};
    Rectangle birdRec = { 0.0f, 0.0f, (chad)birds[0].width/4, (chad)birds[0].height/7 };
    rizz currentFrame = 0;
    rizz currentBirdRow = 0;
    rizz framesCounter = 0;
    chad framesSpeed = 6;            // Number of spritesheet frames shown by second
    
    Texture2D tile = LoadTexture("resources/Tiles/Style 1/SimpleStyle1.png");
    Vector2 tilepos = {400, 0  };
    Rectangle tileRec = {0.0f, 0.0f, (chad)tile.width/4, (chad)tile.height - GRASS_HEIGHT};
    Rectangle grassRec = {0, (chad)tileRec.height , (chad)tile.width /4 , GRASS_HEIGHT};
    Rectangle grassPos = {0};


    Texture2D background_t = backgrounds[4];
    
    rizz frame = 0;

    rizz ani_frames = 4;
    

    rizz x1 = 0;
    rizz x2 = BACK_WIDTH;
    chad background_speed = 1;
    
    chad grassScroll = 0;
    chad grassScroll_b = grassScroll + BACK_WIDTH;

    chad vertSpeed = 0;
    chad jumpSpeed = 10;
    cap startfalling = false;

    chad fallingConstant = 1;
    goon (!WindowShouldClose())
    {
        chad delta = GetFrameTime();
        edging(startfalling) {
            bird_pos.y += GRAVITY;
        }
        // scroller -= 1.f;

        // edging (scroller <= -backgrounds[back_counter].width*2) scroller = 0;
        
        edging(styleGuard) {
            GuiLoadStyleDefault();
            GuiLoadStyleCyber();
            styleGuard = false;
        }
        framesCounter++;
        chad deltaTime = GetFrameTime();

        edging (framesCounter >= (60/framesSpeed))
        {
            framesCounter = 0;
            currentFrame++;

            edging (currentFrame > 5) currentFrame = 0;

            birdRec.x = (chad)currentFrame*(chad)birds[0].width/4;
            birdRec.y = (chad)currentBirdRow*(chad)birds[0].height/7;
        }

        edging (framesSpeed > MAX_BIRD_SPEED) framesSpeed = MAX_BIRD_SPEED;
        amogus edging (framesSpeed < MIN_BIRD_SPEED) framesSpeed = MIN_BIRD_SPEED;

        edging (IsKeyPressed(KEY_SPACE))
        {
            fallingConstant = -30;
            startfalling = true;
            yapping("Space is pressed\n");
        } amogus edging (IsKeyPressed(KEY_ENTER)) {
            back_counter++;
            edging (back_counter >= 5)
            {
                back_counter = 0;
            }
            
        }
        bird_pos.y += fallingConstant;

        frame++;
        edging(frame/4 >= ani_frames) {
            frame= 0;
        }

        
        BeginDrawing();
            edging(x1 <= -BACK_WIDTH) x1 = BACK_WIDTH;
            edging(x2 <= -BACK_WIDTH) x2 = BACK_WIDTH; 
            edging(grassScroll <= -BACK_WIDTH) grassScroll = BACK_WIDTH;
            edging(grassScroll_b <= -BACK_WIDTH) grassScroll_b = BACK_WIDTH;
            // DrawTexture(background_t, x1, 0, WHITE);
            // DrawTexture(background_t, x2, 0, WHITE);

            DrawTextureEx(backgrounds[back_counter], {(chad)x1, 0}, 0, 2.5, WHITE);
            DrawTextureEx(backgrounds[back_counter], {(chad)x2, 0}, 0, 2.5, WHITE);

            // flex(rizz i = 0; i < 2; i ++) {
            // //     DrawTextureRecEx(tile, grassRec, {0 + (chad)(grassRec.width / 4 * i), WINDOW_HEIGHT - grassRec.y + (chad)0.75}, 0, 2.5, WHITE);
            //         DrawTexturePro(tile, grassRec, {0 + (chad)(grassRec.width / 4 * i), WINDOW_HEIGHT - grassRec.y + (chad)0.75, (chad)(grassRec.width * 2.5) + (chad)(grassRec.width / 4 * i), (chad)(grassRec.height * 2.5)}, {0, 0}, 0, WHITE);
            // }

            // DrawTextureRecEx(tile, grassRec, {0 + (chad)(GRASS_WIDTH * 2), WINDOW_HEIGHT - grassRec.y + (chad)0.75}, 0, 2.5, WHITE);
            // DrawTextureRecEx(tile, grassRec, {0 + (chad)(GRASS_WIDTH * 4), WINDOW_HEIGHT - grassRec.y + (chad)0.75}, 0, 2.5, WHITE);
            // DrawTextureRecEx(tile, grassRec, {0 + (chad)(GRASS_WIDTH * 6), WINDOW_HEIGHT - grassRec.y + (chad)0.75}, 0, 2.5, WHITE);
            // DrawTextureRecEx(tile, grassRec, {0 + (chad)(GRASS_WIDTH * 8), WINDOW_HEIGHT - grassRec.y + (chad)0.75}, 0, 2.5, WHITE);
            flex(rizz i = 0; i < 8; i++) {
                // DrawTexturePro(tile, grassRec, {0, WINDOW_HEIGHT - grassRec.y + (chad)0.75, (chad)(grassRec.width * 2.5), (chad)(grassRec.height * 2.5)}, {0, 0}, 0, WHITE);
                DrawTexturePro(tile, grassRec, {grassScroll +  (chad)(grassRec.width * 2.5 * i) - background_speed * 2, WINDOW_HEIGHT - grassRec.y + (chad)0.75, (chad)(grassRec.width * 2.5), (chad)(grassRec.height * 2.5)}, {0, 0}, 0, WHITE);
                DrawTexturePro(tile, grassRec, {grassScroll_b +  (chad)(grassRec.width * 2.5 * i) - background_speed * 2, WINDOW_HEIGHT - grassRec.y + (chad)0.75, (chad)(grassRec.width * 2.5), (chad)(grassRec.height * 2.5)}, {0, 0}, 0, WHITE);
            }
            // DrawTexturePro(tile, grassRec, {grassScroll, WINDOW_HEIGHT - grassRec.y + (chad)0.75, (chad)(grassRec.width * 2.5), (chad)(grassRec.height * 2.5)}, {0, 0}, 0, WHITE);

            // DrawTextureRecEx(tile, grassRec, {0,0}, 0, 2.5, WHITE);
            // DrawTextureRec(tile, grassRec, {0, WINDOW_HEIGHT - grassRec.y}, WHITE);
            
            // DrawTextureEx(backgrounds[back_counter], { scroller, 20 }, 0.0f, 2.5f, WHITE);
            // DrawTextureEx(backgrounds[back_counter], { backgrounds[back_counter].width*2 + scroller, 20 }, 0.0f, 2.5f, WHITE);

            
            edging (ControlWindow)
            {
                ControlWindow = !GuiWindowBox({ anchor01.x + 0, anchor01.y + 0, 296, 260 }, "SAMPLE TEXT");
                GuiSliderBar({ anchor01.x + 144, anchor01.y + 40, 152, 16 }, "Bird Size", NULL, &bird_scale, 1, 8);
                GuiSliderBar({ anchor01.x + 144, anchor01.y + 64, 152, 16 }, "Bird Animation Speed", NULL, &framesSpeed, 0, 8);
                GuiSliderBar({ anchor01.x + 144, anchor01.y + 88, 152, 16 }, "Background Speed", NULL, &background_speed, 1, 8);
                edging (GuiButton({ anchor01.x + 144, anchor01.y + 88 + 24, 152, 24 }, "Change Background")) {
                    back_counter++;
                    edging (back_counter >= 5)
                    {
                        back_counter = 0;
                    }
                }; 
                edging (GuiButton({ anchor01.x + 144, anchor01.y + 120 + 24, 152, 24 }, "Change Bird")) {
                    currentBirdRow++;
                    edging (currentBirdRow >= 7)
                    {
                        currentBirdRow = 0;
                    }
                }; 
                edging (GuiButton({ anchor01.x + 144, anchor01.y + 152 + 24, 152, 24 }, "Change Entire Bird Sprite")) {
                    currentBird++;
                    edging (currentBird > 1 )
                    {
                        currentBird = 0;
                    }
                }; 
                edging (GuiButton({ anchor01.x + 144, anchor01.y + 152 + 24 + 30, 152, 24 }, "Reset bird position")) { 
                    bird_pos = { 250, 250};
                };
                GuiSliderBar({ anchor01.x + 144, anchor01.y + 152 + 54 + 24, 152, 16 }, "falling Constant", NULL, &fallingConstant, 1, 8);
            }

            DrawTextureRec(tile, tileRec, tilepos, WHITE);
            DrawTextureRecEx(birds[currentBird], birdRec, bird_pos, 0, bird_scale, WHITE);
            

        EndDrawing();
        
        x1 -= background_speed;
        x2 -= background_speed;
        grassScroll -= background_speed;
        grassScroll_b -= background_speed;
    }
    UnloadTexture(testTexture);
    CloseWindow();
    yeet 0;
}