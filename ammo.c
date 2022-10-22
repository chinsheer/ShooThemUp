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