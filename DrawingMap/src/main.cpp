#define RAYGUI_IMPLEMENTATION

#include <raylib.h>
#include <string>
#include <iostream>
#include <thread>
#include "variables.hpp"
#include "Movements.hpp"
#include "countingFuncs.hpp"

#define CE_SERIAL_IMPLEMENTATION
#define DEBUG

#include <Communication.h>

using namespace std;

void process_com_data(void *data)
{
    Communication port;
    
    port.init(4);

    float dist = 0;
    float angleLidar = 0;

    do
    {
        port.push_info("1");

        port.take_data();
        dist = port.GetDistance();
        angleLidar = port.GetAngle();

        // Appending walls
        Vector2 coordsWall = roundingToVertSize(countingCoordinates(dist, angleLidar + angleRobot, coordinates), vertexSize);
        graph.makeSeen(coordinates, angleLidar + angleRobot, vertexSize);

        if(graph.find_path(coordinates, graph.countingClosestUnseen(coordinates)).empty())
        {
            graph.unseen->erase(graph.countingClosestUnseen(coordinates));
            graph.append_wall(graph.countingClosestUnseen(coordinates));
        }

        graph.append_wall(coordsWall);
    }while(1);
}

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    // first vertex
    
    vector<Vector2> vec_neighs;
    vec_neighs.push_back({coordinates.x + vertexSize.x, coordinates.y});
    vec_neighs.push_back({coordinates.x - vertexSize.x, coordinates.y});
    vec_neighs.push_back({coordinates.x, coordinates.y + vertexSize.y});
    vec_neighs.push_back({coordinates.x, coordinates.y - vertexSize.y});

    graph.append_vert(coordinates, false);
    (*graph.graph)[coordinates].append_neighbours(vec_neighs);
    vec_neighs.clear();

    InitWindow(screenWidth, screenHeight, "robot view");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------
    camera.target = coordinates;
    camera.rotation = 0.f;
    camera.zoom = 1.f;
    // process_com_data()

    std::thread thread_object(process_com_data, nullptr);

    while ((*graph.graph).size() <= vertexQuantity)
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
                    (*graph.unseen)[vertex.neighbours[i]] = Vertex(vertex.neighbours[i], false);
                }
            }
        }
    }

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {

        //std::cout << (*graph.graph).size() << "\n";
        //-------------------------------------------------------------------------
        // screenShotMap(file_name);
        movementRobot(coordinates, angleRobot);

        movementCamera(cameraCoord, camera);
        camera.target = cameraCoord;
        rotateAndZoom(camera);

        minimapPos = {cameraCoord.x - 100, cameraCoord.y - 200};      
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(WHITE);

        BeginMode2D(camera);
        for (auto wall : *(graph.walls))
        {
            rl_Rectangle recWall = {wall.pos.x, wall.pos.y, vertexSize.x, vertexSize.y};
            DrawRectangleRec(recWall, GREEN);
        }

        DrawRectanglePro({/*coordinate x*/ coordinates.x, /*coordinate y*/ coordinates.y, /*width*/ robotSize.x, /*height*/ robotSize.y},
                         (Vector2){robotSize.x / 2, robotSize.y / 2}, angleRobot, RED);
        
        EndMode2D();

        minimap = LoadTextureFromImage(LoadImageFromScreen());
        DrawRectangleLinesEx({minimapPos.x, minimapPos.y, minimapSize.x, minimapSize.y}, 5.f, BLACK);
        DrawTextureEx(minimap, minimapPos, 0, ((screenHeight * screenWidth) / (minimapSize.x * minimapSize.y)), WHITE);
        // rl_DrawText(text.c_str(), 20.0, 100.0, 10.0, PINK);
        EndDrawing();
        UnloadTexture(minimap);
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    rl_CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}