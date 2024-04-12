#include "countingFuncs.hpp"
Vector2 countingCoordinates(float length, float deg, Vector2 coords)
{
    float x = cos(deg * PI / 180) * length + coords.x;
    float y = sin(deg * PI / 180) * length + coords.y;
    return (Vector2){x, y};
}

Vector2 roundingToVertSize(Vector2 pos, Vector2 vertexSize)
{
    int x, y = 0;
    if (int(pos.x) % int(vertexSize.x) > (vertexSize.x / 2))
    {
        x = (int(pos.x) / int(vertexSize.x) + 1) * vertexSize.x;
    }
    else
    {
        x = int(pos.x) / int(vertexSize.x) * vertexSize.x;
    }

    if (int(pos.y) % int(vertexSize.y) > (vertexSize.y / 2))
    {
        y = (int(pos.y) / int(vertexSize.y) + 1) * vertexSize.y;
    }
    else
    {
        y = int(pos.y) / int(vertexSize.y) * vertexSize.y;
    }
    return {float(x), float(y)};
}

// bool IsPreWallExist(Vector2 posTrueWall, Vector2 lidarPos, Vector2 posWall)
// {
//     float k = (lidarPos.y - posTrueWall.y) / (lidarPos.x - posTrueWall.x);
//     float b = lidarPos.y - k * lidarPos.x;

//     if(int(posWall.y) == int(k * posWall.x + b)){
//         return false;
//     }
//     else{
//         return true;
//     }
// }