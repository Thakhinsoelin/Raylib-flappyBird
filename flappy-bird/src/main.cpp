#include "raylib.h"
#include "raygui.h"
#include "raymath.h"

#define RRES_IMPLEMENTATION
#include "../../rres/src/rres.h"

#define RRES_RAYLIB_IMPLEMENTATION
#include "../../rres/src/rres-raylib.h"
#include <print>

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

int main(int argc, char** argv) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Flappy Bird");
    SetTargetFPS(60);
    int num_of_back = 5;
    Image backgrounds[5] = {0};
    backgrounds[0] = LoadImage("resources/Background/Background1.png");
    backgrounds[1] = LoadImage("resources/Background/Background2.png");
    backgrounds[2] = LoadImage("resources/Background/Background3.png");
    backgrounds[3] = LoadImage("resources/Background/Background4.png");
    backgrounds[4] = LoadImage("resources/Background/Background5.png");

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

    Image tiles = LoadImage("resources/Tiles/Style 1/PipeStyle1.png");
    Image tile_arr[8] = {0};
    tile_arr[0] = ImageCopy(tiles);
    tile_arr[1] = ImageCopy(tiles);
    tile_arr[2] = ImageCopy(tiles);
    tile_arr[3] = ImageCopy(tiles);
    tile_arr[4] = ImageCopy(tiles);
    tile_arr[5] = ImageCopy(tiles);
    tile_arr[6] = ImageCopy(tiles);
    tile_arr[7] = ImageCopy(tiles);

    for(int i = 0; i < 8; i++) {
        int tempx = 32 * i;
        int tempy = 0;
        if(tempx > 96) {
            int rr = tempx / 32;
            tempy = 80;
            switch (rr)
            {
            case 4:
                tempx = 0;
                break;

            case 5:
                tempx = 32;
                break;

            case 6:
                tempx = 64;
                break;

            case 7:
                tempx = 96;
                break;
            
            default:
                break;
            }
            ImageCrop(&tile_arr[i], {
                .x = (float)tempx,
                .y = 0,
                .width = 32,
                .height = 80,
            });
        }

        if(tempx <= 96) {
            ImageCrop(&tile_arr[i], {
                .x = (float)tempx,
                .y = 0,
                .width = 32,
                .height = 80
            });
        }
    }

    Texture2D tileTextureTest1 = LoadTextureFromImage(tile_arr[3]);
    Texture2D tileTextureTest2 = LoadTextureFromImage(tile_arr[6]);

    Image current = backgrounds[4];
    Texture2D background_t = LoadTextureFromImage(current);
    
    int x1 = 0;
    int x2 = BACK_WIDTH;
    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        if (IsKeyPressed(KEY_SPACE))
        {
            std::print("Space is pressed");
        } else if (IsKeyPressed(KEY_ENTER)) {
            num_of_back++;
            if(num_of_back > 4) {
                num_of_back = 0;
            }
            current = backgrounds[num_of_back];
            loadImageWithTexture(background_t, current);
        }
        
        BeginDrawing();
            if(x1 <= -BACK_WIDTH) x1 = BACK_WIDTH;
            if(x2 <= -BACK_WIDTH) x2 = BACK_WIDTH; 
            // DrawTexture(background_t, x1, 0, WHITE);
            // DrawTexture(background_t, x2, 0, WHITE);

            DrawTextureEx(background_t, {.x = (float)x1, .y = 0}, 0, 2.5, WHITE);
            DrawTextureEx(background_t, {.x = (float)x2, .y = 0}, 0, 2.5, WHITE);

            DrawTexture(testTexture, 300,300, WHITE);
            //tile test
            DrawTexture(tileTextureTest1, 0, 0, WHITE);
            DrawTexture(tileTextureTest2, 50, 0, WHITE);
            // DrawTextureEx(background_t, {.x = 0, .y = 0},0,2,PURPLE);
            
        EndDrawing();
        x1--;
        x2--;
    }
    UnloadTexture(testTexture);
    CloseWindow();
    return 0;
}