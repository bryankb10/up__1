#include "raylib.h"
#include <math.h>
#include <time.h>

void drawHourHand(int cx, int cy, int radius, int h, int m, int s) {
    Vector2 startV, endV;
    double theta = (h*60*60+m*60+s) * 2 * PI / (12*60*60);
    double phi = PI / 2 - theta;
    startV.x = cx; startV.y = cy;
    endV.x = 0.60 * radius * cos(phi) + cx;
    endV.y = -0.60 * radius * sin(phi) + cy;
    DrawLineEx(startV, endV, 8, BLACK);
}
void drawMinuteHand(int cx, int cy, int radius, int h, int m, int s){
    Vector2 startV, endV;
    double theta = (h * 60 * 60 + m * 60 + s) * 2 * PI / (60 * 60);
    double phi = PI / 2 - theta;
    startV.x = cx; startV.y = cy;
    endV.x = 0.82 * radius * cos(phi) + cx;
    endV.y = -0.82 * radius * sin(phi) + cy;
    DrawLineEx(startV, endV, 5, BLACK);
}
void drawSecondHand(int cx, int cy, int radius, int h, int m, int s){
    Vector2 startV, endV;
    double theta = (h * 60 * 60 + m * 60 + s) * 2 * PI / 60;
    double phi = PI / 2 - theta;
    startV.x = cx; startV.y = cy;
    endV.x = 0.95 * radius * cos(phi) + cx;
    endV.y = -0.95 * radius * sin(phi) + cy;
    DrawLineEx(startV, endV, 3, RED);
}


void drawClock(int cx, int cy, int radius) {
    DrawCircle (cx, cy, radius, WHITE);
    DrawCircleLines(cx, cy, radius+2, BLACK);
    int i = 0;
    for(i = 0; i<60;i++) {
        double theta = i * 2 * PI/60;
        Vector2 endV, startV;
        endV.x = radius * cos(theta) + cx;
        endV.y = radius * sin(theta) + cy;
        if(i%15 == 0) {
            startV.x = 0.85 * radius * cos(theta) + cx;
            startV.y = 0.85 * radius * sin(theta) + cy;
            DrawLineEx(startV, endV, 7, BLACK);
        }else if (i%5 == 0){
            startV.x = 0.90 * radius * cos(theta) + cx;
            startV.y = 0.90 * radius * sin(theta) + cy;
            DrawLineEx(startV, endV, 4, BLACK);
        }else{
            startV.x = 0.95 * radius * cos(theta) + cx;
            startV.y = 0.95 * radius * sin(theta) + cy;
            DrawLineEx(startV, endV, 1, BLUE);
        }
    }
    time_t t2 = time(NULL);
    struct tm *t = localtime(&t2);
    drawHourHand(cx, cy, radius, t -> tm_hour, t -> tm_min, t -> tm_sec);
    drawMinuteHand(cx, cy, radius, t -> tm_hour, t -> tm_min, t -> tm_sec);
    drawSecondHand(cx, cy, radius, t -> tm_hour, t -> tm_min, t -> tm_sec);
    DrawCircle(cx, cy, 8, BLACK);
        
}

int main(void)
{

    const int screenWidth = 800;
    const int screenHeight = 450;
    const int fontSize = 65;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               

    
    while (!WindowShouldClose())    
    {
        char timestr[100] = {0};
        time_t t;
        t = time(NULL);
        strftime(timestr, 100, "%H:%M:%S", localtime(&t));
        int timestr_w = MeasureText(timestr, fontSize);
        int x = (screenWidth - timestr_w) / 2;
        int y = (screenHeight - fontSize + 100) / 2;
        
        BeginDrawing();

            ClearBackground(RAYWHITE);

            drawClock(400, 225, 200);
            DrawText(timestr, x, y, fontSize, GREEN);

        EndDrawing();
    }

    
    CloseWindow();        
    

    return 0;   
}