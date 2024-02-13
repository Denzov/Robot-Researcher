#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <string>
#include <iostream>
#include <cmath>
#include "variables.hpp"
#include "Movements.hpp"

using namespace std;

Vector2 countingCoordinates(float length, float deg)
{
    float x = cos(deg) * length + x;
    float y = sin(deg) * length + y;
    return (Vector2){x, y};
}


int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------

    InitWindow(screenWidth, screenHeight, "robot view");

    //Font font = LoadFontEx("../src/CALIBRI.TTF", 10, 0, 0);

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------

    camera.target = coordinates;
    camera.rotation = 0.f;
    camera.zoom = 1.f;

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        string text = "distance : " + to_string(dist) + " angle :" + to_string(angle);

        current_time = int(GetTime() * 1000);
        if (current_time - last_time > 500)
        {
            last_time = current_time;
            dist = GetRandomValue(0, 1000);
        }

        screenShotMap(file_name);
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
        DrawRectanglePro({/*coordinate x*/ coordinates.x, /*coordinate y*/ coordinates.y, /*width*/ robotSize.x, /*height*/ robotSize.y},
                         (Vector2){robotSize.x / 2, robotSize.y / 2}, angle, RED);
        DrawLineV(coordinates, countingCoordinates(dist, angle), GREEN);
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