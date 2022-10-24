#include "ammo.h"

typedef struct plane
{
    Vector2 position;
    Vector2 shape[81];
    object_buffer ammo_buffer;
    int size;
    int shootCD;
    int CD;
    int health;

} plane;
plane plane_constructor(Vector2*, int, int, Vector2, int);
void plane_draw(plane);
int plane_cooldown(plane*);
int plane_check_collision(plane, object_buffer*);
bool plane_health_decrease(plane*, int);