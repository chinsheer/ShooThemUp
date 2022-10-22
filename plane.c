#include "plane.h"

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

void draw_ammo(plane *p){ //draw bullet.
    int i = 0;
    ammo *buffer = p->ammo_buffer.buffer;
    while(i < p->ammo_buffer.last){
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
                DrawRectanglePro(buffer->shape, (Vector2){buffer->shape.width/2, buffer->shape.height/2}, buffer->deg, BLACK);
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

bool check_collision(plane p, plane enemy){
    ammo *temp = enemy.ammo_buffer.buffer;
    for(int i = 0; i < enemy.ammo_buffer.last; i++){
        if(temp->alive) if(CheckCollisionRecs((Rectangle){p.position.x - p.size/2, p.position.y - p.size/2, p.size, p.size}, temp->shape)) return true;
        temp++;
    }
    return false;
}
