#include "ammo.h"

typedef struct plane
{
    //draw
    Vector2 position;
    Vector2 shape[81];
    object_buffer ammo_buffer;
    int size;
    //scoreboard and gameplay
    int shootCD;
    int CD;
    int max_health;
    int health;
    int score;
    Rectangle hitbox;
} plane;
plane plane_constructor(Vector2*, int, int, Vector2, int);
void plane_draw(plane);
int plane_cooldown(plane*);
int plane_check_collision(plane, object_buffer*);
bool plane_health_decrease(plane*, int);