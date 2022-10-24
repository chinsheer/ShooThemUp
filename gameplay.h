#include "plane.h"

typedef struct gameUI{
    int width;
    int height;
    Color blackground_color;
    int font_size;

} gameUI;

void gameUI_draw(gameUI, plane, plane**, int, int);