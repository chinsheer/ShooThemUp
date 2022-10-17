#include "raylib.h"
#include "raymath.h"
#include "string.h"
#include "stdlib.h"

Vector2 myAmmoShape[9] = {{0, -1}};

struct monster
{
    struct Vector2 position;
    struct Vector2 shape[81];
};

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
    struct Vector2 direction;
    float rad;
    int dmg;
    int speed;
    int size;
};

struct ammo shoot(Vector2 pos, int speed, int dmg, float angle, int size){
    struct ammo temp;
    temp.alive = 1;
    memset(&(temp.shape), 0, sizeof(temp.shape));
    memcpy(&(temp.shape), myAmmoShape, sizeof(Vector2)*1);
    temp.position = pos;
    
    temp.speed = speed;
    temp.dmg = dmg;
    temp.size = size;

    temp.rad = angle*DEG2RAD;
    temp.direction = Vector2Rotate(Vector2One(), temp.rad);

    return temp;
}

void draw_ammo(struct ammo *buffer, int *counter){ //draw bullet.
    int i = 0;
    while(i < *counter){
        if(buffer->alive){
            if(buffer->position.y <= 0 || 
            buffer->position.y > 900 || 
            buffer->position.x > 1600 || 
            buffer->position.x < 0){
                buffer->alive = 0;
            } else{
                buffer->position = Vector2Add(buffer->position, Vector2Scale(buffer->direction, buffer->speed));
                DrawRectangleV(buffer->position, Vector2Scale(Vector2One(), buffer->size), BLACK);
                struct Vector2 *drawShape = buffer->shape;
                while(!Vector2Equals(*drawShape, Vector2Zero())){
                    DrawRectangleV(Vector2Add(buffer->position, Vector2Scale(*drawShape, buffer->size)), Vector2Scale(Vector2One(), buffer->size), BLACK);
                    drawShape++;
                }
            }
        }
        buffer++;
        i++;
    }
    if(i > 0){
        buffer--;
        if(!(buffer->alive)) (*counter)--;
    }
}

void add_ammo(struct ammo bullet, struct ammo *buffer, int counter){
    int i = 0;
    while(i < counter){
        i++;
        if(!(buffer->alive)){
            *buffer = bullet;
            break;
        }
        buffer++;
    }
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
    struct ammo ammoBuffer[100];
    struct ammo *bp = ammoBuffer;
    memset(&(ammoBuffer), 0, sizeof(ammoBuffer)); //clean ammoBufferMemory
    int ammoBufferCounter = 0;

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
                ammoBufferCounter++;
                add_ammo(shoot(player.position, 3, 10, -135.0f, 10), ammoBuffer, ammoBufferCounter);
            }
        }
        if(IsKeyDown(KEY_X)){
            int a = 0;
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
            draw_ammo(ammoBuffer, &ammoBufferCounter);          

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
