#include "raylib.h"
#include "raymath.h"
#include "string.h"

struct plane
{
    struct Vector2 position;
    struct Vector2 shape[25];

};

int main(void){

    const int screenWidth = 1600;
    const int screenHeight = 900;
    Vector2 playerIntPosition = {800, 450};
    const int playerSize = 10;

    InitWindow(screenWidth, screenHeight, "ShooThemUp");

    SetTargetFPS(60);
    
    //draw player
    struct plane player;
    memset(&(player.shape), 0, sizeof(player.shape)); //clean memory
    Vector2 myPlane[25] = {{0, -1}, {1, 0}, {-1, 0}, {0, 1}, {-1, 1}, {1, 1}, {-2, 2}, {-1, 2}, {0, 2}, {1, 2}, {2, 2}}; //compound literals saves our day
    memmove(&(player.shape), myPlane, sizeof(player.shape));
    

    while (!WindowShouldClose()){
        BeginDrawing();

            ClearBackground(RAYWHITE);
            // player draw section
            Vector2 *playerDrawPixel = player.shape;
            DrawRectangleV(playerIntPosition, Vector2Scale(Vector2One(), playerSize), BLACK);
            while (!Vector2Equals(*playerDrawPixel, Vector2Zero())){
                DrawRectangleV(Vector2Add(playerIntPosition, Vector2Scale(*playerDrawPixel, playerSize)), Vector2Scale(Vector2One(), playerSize), BLACK);
                playerDrawPixel++;
            }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
