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
    DrawRectangleRec((Rectangle){p.position.x, p.position.y, p.size, p.size}, RED);
    while (!Vector2Equals(*temp, Vector2Zero())){
        DrawRectangleRec((Rectangle){(temp->x * p.size) + p.position.x, (temp->y * p.size) + p.position.y , p.size, p.size}, BLACK);
        temp++;
    }
}

int plane_cooldown(plane *p){
    if(p->CD == 0){
        p->CD = p->shootCD;
        return 1;
    }
    p->CD--;
    return 0;
}

int plane_check_collision(plane p, object_buffer *ammo_buffer){
    int dmg = 0;
    ammo *temp = ammo_buffer->buffer;
    for(int i = 0; i < ammo_buffer->last; i++){
        if(temp->alive) {
            if(temp->if_circle){
                if(CheckCollisionCircleRec((Vector2){temp->shape.x, temp->shape.y}, temp->size, (Rectangle){p.position.x, p.position.y, p.size, p.size})){
                    dmg += temp->dmg;
                };
            }
            else{
                if(CheckCollisionRecs((Rectangle){p.position.x - p.size/2, p.position.y - p.size/2, p.size, p.size}, temp->shape)){
                    dmg += temp->dmg;
                };
            }
        }
        temp++;
    } 
    return dmg;
}

bool plane_health_decrease(plane *p, int dmg){
    if(p->health <= dmg){
        return false;
    }
    p->health -= dmg;
    return true;
}
