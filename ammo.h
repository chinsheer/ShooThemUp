#include "raylib.h"
#include "raymath.h"

#include <string.h>
#include <stdbool.h>

typedef struct ammo
{
    int alive;
    Rectangle shape;
    Vector2 direction;
    float deg;
    int dmg;
    int speed;
    int size;
    bool if_circle;
} ammo;

typedef struct object_buffer
{
    int last;
    ammo buffer[2000];
} object_buffer;

typedef struct pattern_session
{
    int frame;
    int frame_end;
} pattern_session;
ammo shoot(Rectangle, int, int, float, int, bool);
void add_ammo(object_buffer*, ammo);
void draw_ammo(object_buffer*);
void monster_pattern1(pattern_session*, object_buffer*, Vector2);


