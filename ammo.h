#include "raylib.h"
#include "raymath.h"

#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

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
    void (*pattern)(object_buffer*, Vector2, Vector2, int*, int*);
} pattern_session;
ammo shoot(Rectangle, int, int, float, int, bool);
void add_ammo(object_buffer*, ammo);
void draw_ammo(object_buffer*);
void monster_pattern1(object_buffer*, Vector2, Vector2, int*, int*);
void monster_pattern2(object_buffer*, Vector2, Vector2, int*, int*);
void monster_pattern3(object_buffer*, Vector2, Vector2, int*, int*);
void monster_pattern_run(pattern_session*, int size, object_buffer*, Vector2, Vector2);
pattern_session monster_pattern_make(int,  void (*pattern)(object_buffer*, Vector2, Vector2, int*, int*));
void monster_pattern_add(pattern_session*, pattern_session, int);

