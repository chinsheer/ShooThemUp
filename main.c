#include "raylib.h"
#include "raymath.h"
#include "string.h"
#include "stdlib.h"

Vector2 myAmmoShape[9] = {{0, -1}};

typedef struct ammo
{
    int alive;
    Vector2 position;
    Vector2 shape[9];
    Vector2 direction;
    float rad;
    int dmg;
    int speed;
    int size;
} ammo;

typedef struct object_buffer
{
    int last;
    ammo buffer[100];
} object_buffer;

typedef struct plane
{
    Vector2 position;
    Vector2 shape[81];
    object_buffer ammo_buffer;
    int size;
    int shootCD;
    int CD;

} plane;

// ammo-------------------------------------------------------------------------

ammo shoot(Vector2 pos, int speed, int dmg, float angle, int size){
    ammo temp;
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

void draw_ammo(plane *p){ //draw bullet.
    int i = 0;
    ammo *buffer = p->ammo_buffer.buffer;
    while(i < p->ammo_buffer.last){
        if(buffer->alive){
            //check if bullet is out of windows
            if(buffer->position.y <= 0 || 
            buffer->position.y > 900 || 
            buffer->position.x > 1600 || 
            buffer->position.x < 0){
                buffer->alive = 0;
            } else{
                //change bullet position
                buffer->position = Vector2Add(buffer->position, Vector2Scale(buffer->direction, buffer->speed));
                //draw bullet and it shape
                DrawRectangleV(buffer->position, Vector2Scale(Vector2One(), buffer->size), BLACK);
                Vector2 *drawShape = buffer->shape;
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
        if(!(buffer->alive)) p->ammo_buffer.last--;
    }
}

void add_ammo(plane *p, ammo bullet){
    ammo *buffer = p->ammo_buffer.buffer;
    p->ammo_buffer.last++;
    int i = 0;
    while(i < p->ammo_buffer.last){
        i++;
        if(!(buffer->alive)){
            *buffer = bullet;
            break;
        }
        buffer++;
    }
}
// ammo-------------------------------------------------------------------------

// plane------------------------------------------------------------------------
plane plane_constructor(Vector2 *shape, int shape_size, int cd, Vector2 position, int size){
    plane temp;
    temp.ammo_buffer.last = 0;
    temp.position = position;
    temp.size = size;
    temp.shootCD = cd;
    temp.CD = 0;
    memset(temp.shape, 0, sizeof(temp.shape));
    memset(temp.ammo_buffer.buffer, 0, sizeof(temp.ammo_buffer.buffer));
    memmove(temp.shape, shape, shape_size);
    return temp;
}

void plane_draw(plane p){
    Vector2 *temp = p.shape;
    DrawRectangleV(p.position, Vector2Scale(Vector2One(), p.size), RED);
    while (!Vector2Equals(*temp, Vector2Zero())){
        DrawRectangleV(Vector2Add(p.position, Vector2Scale(*temp, p.size)), Vector2Scale(Vector2One(), p.size), BLACK);
        temp++;
    }
}

int cooldown(plane *p){
    if(p->CD == 0){
        p->CD = p->shootCD;
        return 1;
    }
    p->CD--;
    return 0;
}

// plane------------------------------------------------------------------------

int main(void){
    //core
    const int screenWidth = 1600;
    const int screenHeight = 900;
    InitWindow(screenWidth, screenHeight, "ShooThemUp");
    SetTargetFPS(60);

    //player
    Vector2 playerIntPosition = {800, 450};
    const int playerSize = 10;
    const int speed = 3;

    //monster
    Vector2  monsterIntPosition = {800, 100};
    const int monsterSize = 10;

    //draw monster
    //set monster shape and properties
    Vector2 myMonster[] = {{4, -4}, {3, -4}, {2, -4}, {1, -4}, {0, -4}, {-1, -4}, {-2, -4}, {-3, -4}, {-4, -4}, 
    {4, -3}, {0, -3}, {-4, -3}, 
    {4, -2}, {0, -2}, {-4, -2}, 
    {4, -1}, {0, -1}, {-4, -1}, {-1, -1}, {1, -1}, 
    {4, 0}, {3, 0}, {2, 0}, {1, 0}, {-1, 0}, {-2, 0}, {-3, 0}, {-4, 0},
    {4, 1}, {3, 1}, {2, 1}, {1, 1}, {-1, 1}, {-2, 1}, {-3, 1}, {-4, 1},
    {4, 2}, {3, 2}, {2, 2}, {-2, 2}, {-3, 2}, {-4, 2},
    {4, 3}, {3, 3}, {2, 3}, {-2, 3}, {-3, 3}, {-4, 3},
    {4, 4}, {3, 4}, {2, 4}, {1, 4}, {0, 4}, {-1, 4}, {-2, 4}, {-3, 4}, {-4, 4}};
    plane test_monster = plane_constructor(myMonster, sizeof(myMonster), 10, monsterIntPosition, 10);
        
    //draw player
    //set player shape and properties
    Vector2 myPlane[] = {{0, -1}, {1, 0}, {-1, 0}, {0, 1}, {-1, 1}, {1, 1}, {-2, 2}, {-1, 2}, {0, 2}, {1, 2}, {2, 2}}; //compound literals saves our day
    plane player = plane_constructor(myPlane, sizeof(myPlane), 10, playerIntPosition, 10);

    //main windows
    while (!WindowShouldClose()){

        //control section
        if(IsKeyDown(KEY_RIGHT)) player.position.x += speed;
        if(IsKeyDown(KEY_LEFT)) player.position.x -= speed;
        if(IsKeyDown(KEY_UP)) player.position.y -= speed;
        if(IsKeyDown(KEY_DOWN)) player.position.y += speed;
        if(IsKeyDown(KEY_Z)) {
            if(cooldown(&player)) add_ammo(&player, shoot(player.position, 3, 10, -135.0f, 10));
        }
        if(IsKeyDown(KEY_X)){
            if(cooldown(&test_monster)) add_ammo(&test_monster, shoot(test_monster.position, 5, 10, 45.0f, 10));
        }

        BeginDrawing();

            ClearBackground(RAYWHITE);
            // player draw section
            plane_draw(player);
            plane_draw(test_monster);
            
            // ammo draw section
            draw_ammo(&player);          
            draw_ammo(&test_monster);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
