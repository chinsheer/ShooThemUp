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

    //pattern_session
    pattern_session pattern1_session;
    pattern1_session.frame_end = 300;
    pattern1_session.frame = 0;

    //main windows
    while (!WindowShouldClose()){

        //hitbox check
       
        if(plane_check_collision(player, &(test_monster.ammo_buffer))){
            gameover = true;
        }

        plane_health_decrease(&(test_monster), plane_check_collision(test_monster, &(player.ammo_buffer)));

        //control section
        if(IsKeyDown(KEY_RIGHT)) player.position.x += speed;
        if(IsKeyDown(KEY_LEFT)) player.position.x -= speed;
        if(IsKeyDown(KEY_UP)) player.position.y -= speed;
        if(IsKeyDown(KEY_DOWN)) player.position.y += speed;
        if(IsKeyDown(KEY_Z)) {
            if(plane_cooldown(&player)) {
                add_ammo(&(player.ammo_buffer), shoot((Rectangle){player.position.x + 5, player.position.y + 10,
                 20, 10}, //shape of it
                 3, //speed
                 10, //damage
                 -90.0f, //rotate
                 10, //size
                 false)); //if Circle
            }
        }
        if(IsKeyDown(KEY_X)){
            /* if(cooldown(&test_monster)) {
                for(int i = 0; i < 10; i++){
                add_ammo(&(test_monster.ammo_buffer), shoot((Rectangle){test_monster.position.x, test_monster.position.y, 
                20, 10}, //shape
                2, //speed
                10, //damage
                15.0f*i + 15.0f, //rotate
                10, //size
                true)); //if circle
                }
            } */
            
        }

        // monster section
        monster_pattern1(&pattern1_session, &(test_monster.ammo_buffer), test_monster.position);


        BeginDrawing();
        if(!gameover){
            //test

            ClearBackground(RAYWHITE);

            // ammo draw section
            draw_ammo(&(player.ammo_buffer));          
            draw_ammo(&(test_monster.ammo_buffer));

            // player draw section
            plane_draw(player);
            plane_draw(test_monster);

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
