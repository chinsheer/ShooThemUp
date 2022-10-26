#include "ammo.h"

ammo shoot(Rectangle shape, int speed, int dmg, float angle, int size, bool if_circle){
    ammo temp;
    temp.alive = 1;
    temp.shape = shape;
    
    temp.speed = speed;
    temp.dmg = dmg;
    temp.size = size;

    temp.deg = angle;
    temp.direction = Vector2Rotate((Vector2){1, 0}, angle*DEG2RAD);
    temp.if_circle = if_circle;
    
    return temp;
}

void add_ammo(object_buffer *ammo_buffer, ammo bullet){
    ammo *buffer = ammo_buffer->buffer;
    int i = 0;
    while(i < ammo_buffer->last){
        i++;
        if(!(buffer->alive)){
            *buffer = bullet;
            return;
        }
        buffer++;
    }
    *buffer = bullet;
    ammo_buffer->last++;
}

void draw_ammo(object_buffer *ammo_buffer){ //draw bullet.
    int i = 0;
    ammo *buffer = ammo_buffer->buffer;
    while(i < ammo_buffer->last){
        if(buffer->alive){
            //check if bullet is out of windows
            if(buffer->shape.y <= 0 || 
            buffer->shape.y > 900 || 
            buffer->shape.x > 1600 || 
            buffer->shape.x < 0){
                buffer->alive = 0;
            } else{
                //change bullet position
                Vector2 position = Vector2Add((Vector2){buffer->shape.x, buffer->shape.y}, Vector2Scale(buffer->direction, buffer->speed));
                buffer->shape.x = position.x;
                buffer->shape.y = position.y;
                //draw bullet and it shape
                if(buffer->if_circle) DrawCircle(buffer->shape.x, buffer->shape.y, buffer->size, BLACK);
                else DrawRectanglePro(buffer->shape, (Vector2){buffer->shape.width/2, buffer->shape.height/2}, buffer->deg, BLACK);
            }
        }
        buffer++;
        i++;
    }
    if(i > 0){
        while (!((--buffer)->alive)){
            (ammo_buffer->last)--;
        }
    }
}

//attack pattern

void monster_pattern1(object_buffer *bullet_buffer, Vector2 pos, Vector2 target, int *frame_end, int *frame){
    if(*frame <= *frame_end && (*frame % 30 == 0)){
        int offset = floor(*frame / 30);
        offset = offset >= 5 ? 10 - offset : offset;
        for(int i = 0; i < 20; i++){
            add_ammo(bullet_buffer, shoot((Rectangle){pos.x, pos.y, 20, 10},
            2, //speed
            10, //damage
            7.5f*i + offset*5.0f, //rotate
            10, //size
            true)); //if circle
        }
    }
    (*frame)++;
}

void monster_pattern2(object_buffer *bullet_buffer, Vector2 pos, Vector2 target, int *frame_end, int *frame){
    if(*frame <= *frame_end && (*frame % 15 == 0)){
        int offset = floor(*frame / 15);
        for(int i = 0; i < 48; i++){
            add_ammo(bullet_buffer, shoot((Rectangle){pos.x, pos.y, 20, 10},
            2,
            10,
            7.5f*i + offset*5.0f,
            10,
            true));
        }
    }
    (*frame)++;
}

void monster_pattern3(object_buffer *bullet_buffer, Vector2 pos, Vector2 target, int *frame_end, int *frame){
    if(*frame <= *frame_end && (*frame % 10 == 0)){
        int offset = floor(*frame / 2);
        offset = offset % 150;
        offset = offset >= 75 ? 150 - offset : offset;
        for(int i = 0; i < 3; i++){
        add_ammo(bullet_buffer, shoot((Rectangle){pos.x, pos.y, 20, 10},
            3,
            10,
            offset + 45*i,
            10,
            true));
        add_ammo(bullet_buffer, shoot((Rectangle){pos.x, pos.y, 20, 10},
            3,
            10,
            90 - offset + 45*i,
            10,
            true));
        }
        
    }
    (*frame)++;
}

void monster_pattern_run(pattern_session *session_buffer, int size, object_buffer *bullet_buffer, Vector2 pos, Vector2 target){
    pattern_session *index = session_buffer;
    for(int i = 0; i < size; i++){
        if(index->frame_end != 0){
            if(index->frame_end <= index->frame){
            switch(rand() % 3){
                case 0:
                    monster_pattern_add(session_buffer, monster_pattern_make(300, monster_pattern1), 3);
                    break;
                case 1:
                    monster_pattern_add(session_buffer, monster_pattern_make(300, monster_pattern2), 3);
                    break;
                case 2:
                    monster_pattern_add(session_buffer, monster_pattern_make(300, monster_pattern3), 3);
                    break;
            }
            }
            index->pattern(bullet_buffer, pos, target, &(index->frame_end), &(index->frame));
        }
    
        index++;
    }
}

pattern_session monster_pattern_make(int frame_end, void (*pattern)(object_buffer*, Vector2, Vector2, int*, int*)){
    pattern_session temp;
    temp.frame_end = frame_end;
    temp.frame = 0;
    temp.pattern = pattern;
    return temp;
}

void monster_pattern_add(pattern_session *session_buffer, pattern_session session, int size){
    pattern_session *index = session_buffer;
    int i = 0;
    while(i < size){
        if(index->frame_end <= index->frame){
            *index = session;
            break;
        }
        index++;
    }
}

