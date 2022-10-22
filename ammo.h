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
} ammo;

typedef struct object_buffer
{
    int last;
    ammo buffer[2000];
} object_buffer;
ammo shoot(Rectangle, int, int, float, int);

