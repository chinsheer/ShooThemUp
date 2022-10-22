#include "ammo.h"

typedef struct plane
{
    Vector2 position;
    Vector2 shape[81];
    object_buffer ammo_buffer;
    int size;
    int shootCD;
    int CD;

} plane;
plane plane_constructor(Vector2*, int, int, Vector2, int);
void plane_draw(plane);
int cooldown(plane*);
void draw_ammo(plane*);
void add_ammo(plane*, ammo);
bool check_collision(plane, plane);
