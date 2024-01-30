#include <raylib.h>
#include <string>
#include <iostream>
#define RAYGUI_IMPLEMENTATION
#include "extras/raygui.h"
#include "variables.hpp"
#include "block.hpp"

using namespace std;

bool CheckPos(Vector2 positionBlock, std::vector<Block> blocks)
{ // true - if has not existed yet
    float k = positionBlock.y / positionBlock.x;
    for (int i = 0; i < blocks.size(); ++i)
    {
        if (blocks[i].position.y / blocks[i].position.x == k)
        {
            return false;
        }
    }
    return true;
}

void addingBlock(vector<Block> &blocks, float dist, float degree, Vector2 currentPos)
{
    Block block;
    block.setX(degree, dist, currentPos);
    block.setY(degree, dist, currentPos);

    // Checking position
    if (CheckPos(block.position, blocks))
    {
        blocks.emplace_back(block);
    }
}

void movementRobot(Vector2 &coord, float &degree)
{
    if (IsKeyDown(KEY_W)){
        coord.y += 10 * sin(degree * PI / 180);
        coord.x += 10 * cos(degree * PI / 180);
    }
    if (IsKeyDown(KEY_A)){
        degree -= 5;
    }
    if (IsKeyDown(KEY_D)){
        degree += 5;
    }
    if (IsKeyDown(KEY_S)){
        coord.y -= 10 * sin(degree * PI / 180);
        coord.x -= 10 * cos(degree * PI / 180);
    }
}

void movementCamera(Vector2 &coord)
{
    if (IsKeyDown(KEY_LEFT))
    {
        coord.x -= 10;
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        coord.x += 10;
    }
    else if (IsKeyDown(KEY_UP))
    {
        coord.y -= 10;
    }
    else if (IsKeyDown(KEY_DOWN))
    {
        coord.y += 10;
    }
}

void rotateAndZoom(Camera2D &cam)
{
    // Rotation
    if (IsKeyDown(KEY_Q))
        cam.rotation -= 0.5;
    else if (IsKeyDown(KEY_E))
        cam.rotation += 0.5;
    // Zoom
    cam.zoom += (GetMouseWheelMove() * 0.05);
    if (cam.zoom > 3.0f)
        cam.zoom = 3.0f;
    else if (cam.zoom < 0.1f)
        cam.zoom = 0.1f;
    // Reset all
    if (IsKeyPressed(KEY_R))
    {
        cam.zoom = 1.0f;
        cam.rotation = 0.0f;
    }
}

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------

    InitWindow(screenWidth, screenHeight, "robot view");

    Font font = LoadFontEx("CALIBRI.TTF", 10, 0, 0);

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------

    camera.target = coordinates;
    camera.rotation = 0.f;
    camera.zoom = 1.f;

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        game_time = (int)(GetTime() * 1000);
        if (game_time - previous_time > 500)
        {
            dist = GetRandomValue(1, 2500);
            previous_time = game_time;
        }
        // Update
        //----------------------------------------------------------------------------------
        string text = "distance : " + to_string(dist) + " angle :" + to_string(angle);

        addingBlock(walls, dist, angle, coordinates);
        movementRobot(coordinates, angle);

        movementCamera(cameraCoord);
        camera.target = cameraCoord;
        rotateAndZoom(camera);

        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(WHITE);

        BeginMode2D(camera);
        for (int i = 0; i < walls.size(); ++i)
        {
            DrawRectangleV(walls[i].position, walls[i].size, walls[i].color);
        }
        DrawRectanglePro({/*coordinate x*/coordinates.x, /*coordinate y*/coordinates.y, /*width*/robotSize.x, /*height*/robotSize.y},
                    (Vector2){robotSize.x / 2, robotSize.y / 2}, angle, RED);
        DrawLineV(coordinates, walls[walls.size() - 1].position, GREEN);

        EndMode2D();

        DrawText(text.c_str(), 20.0, 100.0, 10.0, MAROON);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}