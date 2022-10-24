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
    ammo_buffer->last++;
    int i = 0;
    while(i < ammo_buffer->last){
        i++;
        if(!(buffer->alive)){
            *buffer = bullet;
            break;
        }
        buffer++;
    }
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
        buffer--;
        if(!(buffer->alive)) ammo_buffer->last--;
    }
}

//attack pattern

void monster_pattern1(pattern_session *session, object_buffer *bullet_buffer, Vector2 pos){
    if(session->frame <= session->frame_end && (session->frame % 30 == 0)){
        int offset = floor(session->frame / 30);
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
    session->frame++;
}
