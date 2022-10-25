#include "main.h"

int main(void){
    //core
    srand(time(NULL));
    bool gameover = false;
    const int screenWidth = 1600;
    const int screenHeight = 900;
    InitWindow(screenWidth, screenHeight, "ShooThemUp");
    SetTargetFPS(60);

    //gameplay
    gameUI UI;
    UI.height = screenHeight;
    UI.width = 400;
    UI.font_size = 36;
    UI.blackground_color = LIGHTGRAY;

    //player
    Vector2 playerIntPosition = {600, 450};
    const int playerSize = 10;
    const int speed = 2;

    //monster
    Vector2  monsterIntPosition = {600, 100};
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
    test_monster.max_health = 200;
    test_monster.health = 190;
    plane *monster_buffer[2] = {&test_monster, 0};
    test_monster.hitbox = (Rectangle){-4, -4, 9, 9};
        
    //draw player
    //set player shape and properties
    Vector2 myPlane[] = {{0, -1}, {1, 0}, {-1, 0}, {0, 1}, {-1, 1}, {1, 1}, {-2, 2}, {-1, 2}, {0, 2}, {1, 2}, {2, 2}}; //compound literals saves our day
    plane player = plane_constructor(myPlane, 
    sizeof(myPlane), 
    10, //cd
    playerIntPosition, 
    playerSize);
    player.hitbox = (Rectangle){0, 0, 1, 1};

    //pattern_session
    pattern_session pattern_buffer[3] = {0};
    pattern_buffer[0] = monster_pattern_make(300, monster_pattern1);

    //main windows
    while (!WindowShouldClose()){

        //hitbox check
       
        if(plane_check_collision(player, &(test_monster.ammo_buffer))){
            gameover = true;
        }

        plane_health_decrease(&(test_monster), plane_check_collision(test_monster, &(player.ammo_buffer)));

        //control section
        if(IsKeyDown(KEY_RIGHT)) if(player.position.x + speed < screenWidth - UI.width) player.position.x += speed;
        if(IsKeyDown(KEY_LEFT)) if(player.position.x - speed > 0) player.position.x -= speed;
        if(IsKeyDown(KEY_UP)) if(player.position.y - speed > 0) player.position.y -= speed;
        if(IsKeyDown(KEY_DOWN)) if(player.position.y + speed < screenHeight) player.position.y += speed;
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
        /* monster_pattern1(&pattern1_session, &(test_monster.ammo_buffer), test_monster.position, player.position);
        monster_pattern2(&pattern2_session, &(test_monster.ammo_buffer), test_monster.position, player.position);
        monster_pattern3(&pattern3_session, &(test_monster.ammo_buffer), test_monster.position, player.position); */
        monster_pattern_run(pattern_buffer, 3, &(test_monster.ammo_buffer), test_monster.position, player.position);


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

            //ui_panel draw
            gameUI_draw(UI, player, monster_buffer, screenWidth, screenHeight);
            

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