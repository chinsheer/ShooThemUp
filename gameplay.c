#include "gameplay.h"

//Score will show on the right so everything write on this shit will be (screen_width - gameUI_width + x, y)

void gameUI_draw(gameUI ui, plane p, plane **monster, int windows_width, int windows_height){
    int content_x_left = windows_width - ui.width;
    int margin = 50;
    Rectangle layout = {content_x_left, 0, ui.width, ui.height};
    Rectangle health_bar1 = {content_x_left + margin, 350, (*monster)->health * 200 / (*monster)->max_health, 30};
    Rectangle health_bar1_outlines = {content_x_left + margin, 350, 200, 30};
    //draw background
    DrawRectangleRec(layout, ui.blackground_color);

    //score section
    DrawText("Score", content_x_left + margin, 100, ui.font_size, BLACK);
    DrawText(TextFormat("%08i", p.score), content_x_left + margin, 150, ui.font_size, BLACK);

    //temporary use health bar section
    DrawText("Monster", content_x_left + margin, 300, ui.font_size, BLACK);
    DrawRectangleLinesEx(health_bar1_outlines, 5, BLACK);
    DrawRectangleRec(health_bar1, BLACK);
}