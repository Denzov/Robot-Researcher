#include <raylib.h>
#include <string>
#include <iostream>
#define RAYGUI_IMPLEMENTATION
#include "extras/raygui.h"
#include "variables.hpp"

using namespace std;

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

void screenShotMap(){
    if(IsKeyPressed(KEY_F1)){
        TakeScreenshot(file_name.c_str());
    }
}

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------

    InitWindow(screenWidth, screenHeight, "robot view");

    Font font = LoadFontEx("../src/CALIBRI.TTF", 10, 0, 0);

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------

    camera.target = coordinates;
    camera.rotation = 0.f;
    camera.zoom = 1.f;

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        string text = "distance : " + to_string(dist) + " angle :" + to_string(angle);

        current_time = int(GetTime() * 1000);
        if(current_time - last_time > 500){
            last_time = current_time;
            dist = randomValue(0, 1000);
        }


        screenShotMap();
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
        DrawRectanglePro({/*coordinate x*/coordinates.x, /*coordinate y*/coordinates.y, /*width*/robotSize.x, /*height*/robotSize.y},
                    (Vector2){robotSize.x / 2, robotSize.y / 2}, angle, RED);
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