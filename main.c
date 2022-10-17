#include "raylib.h"
#include "raymath.h"
#include "string.h"
#include "stdlib.h"

Vector2 myAmmoShape[9] = {{0, -1}};

struct plane
{
    struct Vector2 position;
    struct Vector2 shape[25];
    int shootCD;

};

struct ammo
{
    int alive;
    struct Vector2 position;
    struct Vector2 shape[9];
    int dmg;
    int speed;
};

struct ammo shoot(struct plane playerShoot, int speed, int dmg){
    struct ammo temp;
    temp.alive = 1;
    memset(&(temp.shape), 0, sizeof(temp.shape));
    memcpy(&(temp.shape), myAmmoShape, sizeof(Vector2)*1);
    temp.position = playerShoot.position;

    temp.speed = speed;
    temp.dmg = dmg;

    return temp;
}

int main(void){
    //core
    const int screenWidth = 1600;
    const int screenHeight = 900;

    //player
    Vector2 playerIntPosition = {800, 450};
    const int playerSize = 10;
    const int speed = 3;

    //ammo
    const int ammoSize = 10;
    InitWindow(screenWidth, screenHeight, "ShooThemUp");

    SetTargetFPS(60);
    
    //draw player
    struct plane player;
    player.shootCD = 0;
    memset(&(player.shape), 0, sizeof(player.shape)); //clean memory
    Vector2 myPlane[25] = {{0, -1}, {1, 0}, {-1, 0}, {0, 1}, {-1, 1}, {1, 1}, {-2, 2}, {-1, 2}, {0, 2}, {1, 2}, {2, 2}}; //compound literals saves our day
    memmove(&(player.shape), myPlane, sizeof(player.shape));
    player.position = playerIntPosition;

    //ammo section
    struct ammo ammoBuffer[20];
    memset(&(ammoBuffer), 0, sizeof(ammoBuffer)); //clean ammoBufferMemory

    //main windows
    while (!WindowShouldClose()){

        //gameplay section
        if(player.shootCD > 0) player.shootCD--;

        //control section
        if(IsKeyDown(KEY_RIGHT)) player.position.x += speed;
        if(IsKeyDown(KEY_LEFT)) player.position.x -= speed;
        if(IsKeyDown(KEY_UP)) player.position.y -= speed;
        if(IsKeyDown(KEY_DOWN)) player.position.y += speed;
        if(IsKeyDown(KEY_Z)) {
            if(player.shootCD == 0){
                player.shootCD = 10;
                struct ammo *ammoTemp = ammoBuffer;
                while (ammoTemp->alive){
                    ammoTemp++;
                }
                *ammoTemp = shoot(player, 3, 10);
            }
        }

        BeginDrawing();

            ClearBackground(RAYWHITE);
            // player draw section
            Vector2 *playerDrawPixel = player.shape;
            DrawRectangleV(player.position, Vector2Scale(Vector2One(), playerSize), BLACK);
            while (!Vector2Equals(*playerDrawPixel, Vector2Zero())){
                DrawRectangleV(Vector2Add(player.position, Vector2Scale(*playerDrawPixel, playerSize)), Vector2Scale(Vector2One(), playerSize), BLACK);
                playerDrawPixel++;
            }

            // ammo draw section
            struct ammo *ammoTemp = ammoBuffer;
            while (ammoTemp->alive){
                if(ammoTemp->position.y <= 0){
                    ammoTemp->alive = 0;
                } else{
                    ammoTemp->position.y -= ammoTemp->speed;
                    DrawRectangleV(ammoTemp->position, Vector2Scale(Vector2One(), ammoSize), BLACK);
                    DrawRectangleV(Vector2Add(ammoTemp->position, Vector2Scale(ammoTemp->position, ammoSize)), Vector2Scale(Vector2One(), ammoSize), BLACK);
                }
                ammoTemp++;
                
            }
            

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
