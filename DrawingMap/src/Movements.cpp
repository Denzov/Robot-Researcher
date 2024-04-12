#include <cmath>
#include "Movements.hpp"

void movementRobot(Vector2 &coord, float &degree)
{
    if (IsKeyDown(KEY_W))
    {
        coord.y += 10 * sin(degree * PI / 180);
        coord.x += 10 * cos(degree * PI / 180);
    }
    if (IsKeyDown(KEY_A))
    {
        degree -= 5;
    }
    if (IsKeyDown(KEY_D))
    {
        degree += 5;
    }
    if (IsKeyDown(KEY_S))
    {
        coord.y -= 10 * sin(degree * PI / 180);
        coord.x -= 10 * cos(degree * PI / 180);
    }
}

void movementCamera(Vector2 &coord, Camera2D &cam)
{
    if (IsKeyDown(KEY_LEFT))
    {
        coord.x -= 10/cam.zoom ;
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        coord.x += 10/cam.zoom ;
    }
    else if (IsKeyDown(KEY_UP))
    {
        coord.y -= 10/cam.zoom ;
    }
    else if (IsKeyDown(KEY_DOWN))
    {
        coord.y += 10/cam.zoom ;
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
    cam.zoom += (GetMouseWheelMove() * 0.05)/2;
    if (cam.zoom > 3.0f)
        cam.zoom = 3.0f;
    // Reset all
    if (IsKeyPressed(KEY_R))
    {
        cam.zoom = 1.0f;
        cam.rotation = 0.0f;
    }
}

void screenShotMap(std::string file)
{
    if (IsKeyPressed(KEY_F1))
    {
        TakeScreenshot(file.c_str());
    }
}