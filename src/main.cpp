#include "raylib.h"
#include "resource_dir.h"
#include <iostream>
#include <cmath>


int main(void)
{

    InitWindow(800, 600, "waving tiles");
    SearchAndSetResourceDir("resources");
    SetTargetFPS(60);

    Texture2D iso_tile = LoadTexture("isometric_tile.png");
    int tileOffsetX = -iso_tile.width/2 + GetScreenWidth()/2;
    int tileOffsetY = GetScreenHeight()/4;
    float zOscillation = 0.0f;
    int interval = 0;
    std::cout << tileOffsetX << " " << tileOffsetY << "\n";
    Vector2 iHat = {1.0f, 0.5f};
    Vector2 jHat = {-1.0f, 0.5f};
    Vector2 tilePosVec = {0.0f, 0.0f};
    Vector2 tileIsoPosVec;

    
    while (!WindowShouldClose())
    
    {
        float time = GetTime();
        float speed = 5.0f;
        float amplitude = 10.0f;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawGrid(10, 10.0f);
        
        for (tilePosVec.x = 0; tilePosVec.x < 10; tilePosVec.x++)
        {
            for (tilePosVec.y = 0; tilePosVec.y < 10; tilePosVec.y++)
            {
                float phase = (tilePosVec.x + tilePosVec.y) * PI / 4.0f;
                zOscillation = sinf(time * speed + phase);
                tileIsoPosVec ={tilePosVec.x*iHat.x/2 + tilePosVec.y*jHat.x/2, 
                                tilePosVec.x*iHat.y/2 + tilePosVec.y*jHat.y/2 };
                DrawTexture(iso_tile,
                            tileIsoPosVec.x * iso_tile.width + tileOffsetX,
                            tileIsoPosVec.y * iso_tile.height + tileOffsetY + zOscillation*10,
                            WHITE);
            }
        }
        EndDrawing();
    }
    UnloadTexture(iso_tile);
    CloseWindow();
    return 0;
}
