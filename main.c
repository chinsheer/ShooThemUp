#include "main.h"

int main(void){
    //core
    bool gameover = false;
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
    plane test_monster = plane_constructor(myMonster, 
    sizeof(myMonster), 
    40, //cd
    monsterIntPosition, 
    10);
        
    //draw player
    //set player shape and properties
    Vector2 myPlane[] = {{0, -1}, {1, 0}, {-1, 0}, {0, 1}, {-1, 1}, {1, 1}, {-2, 2}, {-1, 2}, {0, 2}, {1, 2}, {2, 2}}; //compound literals saves our day
    plane player = plane_constructor(myPlane, 
    sizeof(myPlane), 
    10, //cd
    playerIntPosition, 
    playerSize);

    //main windows
    while (!WindowShouldClose()){

        //hitbox check
       
        if(check_collision(player, test_monster)){
            gameover = true;
        }

        //control section
        if(IsKeyDown(KEY_RIGHT)) player.position.x += speed;
        if(IsKeyDown(KEY_LEFT)) player.position.x -= speed;
        if(IsKeyDown(KEY_UP)) player.position.y -= speed;
        if(IsKeyDown(KEY_DOWN)) player.position.y += speed;
        if(IsKeyDown(KEY_Z)) {
            if(cooldown(&player)) {
                add_ammo(&player, shoot((Rectangle){player.position.x + 5, player.position.y + 10,
                 20, 10}, //shape of it
                 3, //speed
                 10, //damage
                 -90.0f, //rotate
                 10, //size
                 false)); //if Circle
            }
        }
        if(IsKeyDown(KEY_X)){
            if(cooldown(&test_monster)) {
                for(int i = 0; i < 10; i++){
                add_ammo(&test_monster, shoot((Rectangle){test_monster.position.x, test_monster.position.y, 
                20, 10}, //shape
                2, //speed
                10, //damage
                15.0f*i + 15.0f, //rotate
                10, //size
                true)); //if circle
                }
            }
            
        }
        BeginDrawing();
        if(!gameover){
            //test

            ClearBackground(RAYWHITE);
            // player draw section
            plane_draw(player);
            plane_draw(test_monster);

            // ammo draw section
            draw_ammo(&player);          
            draw_ammo(&test_monster);

        
        } else{
            break;
        }
        EndDrawing();
    }
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("LOL You suck.", 700, 400, 36, BLACK);
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
