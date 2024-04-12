#define RAYGUI_IMPLEMENTATION

#include <raylib.h>
#include <string>
#include <iostream>
#include <cmath>
#include "variables.hpp"
#include "Movements.hpp"

#define CE_SERIAL_IMPLEMENTATION
#define DEBUG

#include <Communication.h>

using namespace std;

Vector2 countingCoordinates(float length, float deg, Vector2 coords)
{
    float x = cos(deg * PI / 180) * length + coords.x;
    float y = sin(deg * PI / 180) * length + coords.y;
    return (Vector2){x, y};
}

Vector2 roundingToVertSize(Vector2 pos)
{
    int x, y = 0;
    if (int(pos.x) % int(vertexSize.x) > (vertexSize.x / 2))
    {
        x = (int(pos.x) / int(vertexSize.x) + 1) * vertexSize.x;
    }
    else{
        x = int(pos.x) / int(vertexSize.x) * vertexSize.x;
    }

    if (int(pos.y) % int(vertexSize.y) > (vertexSize.y / 2))
    {
        y = (int(pos.y) / int(vertexSize.y) + 1) * vertexSize.y;
    }
    else{
        y = int(pos.y) / int(vertexSize.y) * vertexSize.y;
    }
    return {x, y};
}

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    
    Communication port;
	port.init(4);

	// string s = "101|5";
	// port.push_info(s.c_str());
    InitWindow(screenWidth, screenHeight, "robot view");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------

    // first vertex
    vector<Vector2> vec_neighs;
    vec_neighs.push_back({coordinates.x + vertexSize.x, coordinates.y});
    vec_neighs.push_back({coordinates.x - vertexSize.x, coordinates.y});
    vec_neighs.push_back({coordinates.x, coordinates.y + vertexSize.y});
    vec_neighs.push_back({coordinates.x, coordinates.y - vertexSize.y});

    graph.append_vert(coordinates, false);
    (*graph.graph)[coordinates].append_neighbours(vec_neighs);
    vec_neighs.clear();

    camera.target = coordinates;
    camera.rotation = 0.f;
    camera.zoom = 1.f;

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
		port.take_data();
        dist = port.GetDistance();
        angle = port.GetAngle();
        string text = "distance : " + to_string(dist) + " angle :" + to_string(angle);

        //------------------------------------------------------------------------
        // Appending vertexes
        if ((*graph.graph).size() <= vertexQuantity)
        {
            for (auto &[pos, vertex] : (*graph.graph))
            {
                if (vertex.neighbours.size() <= 4)
                {
                    vec_neighs.push_back({pos.x + vertexSize.x, pos.y});
                    vec_neighs.push_back({pos.x - vertexSize.x, pos.y});
                    vec_neighs.push_back({pos.x, pos.y + vertexSize.y});
                    vec_neighs.push_back({pos.x, pos.y - vertexSize.y});
                    (*graph.graph)[pos].append_neighbours(vec_neighs);
                    vec_neighs.clear();
                }
            }

            for (auto &[pos, vertex] : *(graph.graph))
            {
                if (vertex.neighbours.size() <= 4)
                {
                    for (int i = 0; i < vertex.neighbours.size(); i++)
                    {
                        graph.append_vert(vertex.neighbours[i], false);
                    }
                }
            }
        }
        //------------------------------------------------------------------------

        // Appending walls
        Vector2 coordsWall = roundingToVertSize(countingCoordinates(dist, angle + degree, coordinates));

        graph.append_wall(coordsWall);
        //-------------------------------------------------------------------------
        screenShotMap(file_name);
        movementRobot(coordinates, degree);

        movementCamera(cameraCoord);
        camera.target = cameraCoord;
        rotateAndZoom(camera);

        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(WHITE);

        BeginMode2D(camera);

        // Draw vertexes
        // for (auto &[pos, vertex] : *(graph.graph))
        // {
        //     rl_Rectangle recVert = {pos.x, pos.y, vertexSize.x, vertexSize.y};
        //     DrawRectangleLinesEx(recVert, 1 / camera.zoom, GREEN);
        // }
        for(auto &[pos, wall] : *(graph.walls)){
            rl_Rectangle recWall = {pos.x, pos.y, vertexSize.x, vertexSize.y};
            DrawRectangleRec(recWall, GREEN);
        }

        DrawRectanglePro({/*coordinate x*/ coordinates.x, /*coordinate y*/ coordinates.y, /*width*/ robotSize.x, /*height*/ robotSize.y},
                         (Vector2){robotSize.x / 2, robotSize.y / 2}, degree, RED);
        DrawRectanglePro({coordinates.x + robotSize.x / 2, coordinates.y, lidarSize.x, lidarSize.y},
                        {robotSize.x / 2, robotSize.y / 2}, angle, BLACK);
        DrawLineV(coordinates, countingCoordinates(dist, angle + degree, coordinates), VIOLET);
        EndMode2D();

        rl_DrawText(text.c_str(), 20.0, 100.0, 10.0, PINK);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    rl_CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}