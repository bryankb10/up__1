#include "raylib.h"
#include <math.h>
#include <time.h>

void drawHourHand(int cx, int cy, int radius, int h, int m, int s) {
    Vector2 startV, endV;
    double theta = (h*60*60+m*60+s) * 2 * PI / (12*60*60);
    double phi = PI / 2 - theta;
    startV.x = cx; startV.y = cy;
    endV.x = 0.55 * radius * cos(phi) + cx;
    endV.y = -0.55 * radius * sin(phi) + cy;
    DrawLineEx(startV, endV, 11, BLACK);
}
void drawMinuteHand(int cx, int cy, int radius, int h, int m, int s){
    Vector2 startV, endV;
    double theta = (h * 60 * 60 + m * 60 + s) * 2 * PI / (60 * 60);
    double phi = PI / 2 - theta;
    startV.x = cx; startV.y = cy;
    endV.x = 0.85 * radius * cos(phi) + cx;
    endV.y = -0.85 * radius * sin(phi) + cy;
    DrawLineEx(startV, endV, 8, BLACK);
}
void drawSecondHand(int cx, int cy, int radius, int h, int m, int s){
    Vector2 startV, endV;
    double theta = (h * 60 * 60 + m * 60 + s) * 2 * PI / 60;
    double phi = PI / 2 - theta;
    startV.x = cx; startV.y = cy;
    endV.x = 0.78 * radius * cos(phi) + cx;
    endV.y = -0.78 * radius * sin(phi) + cy;
    DrawLineEx(startV, endV, 5, RED);
}


void drawClock(int cx, int cy, int radius, int ex, int ey) {
    Rectangle rec = {(cx-ex)/2,(cy-ey)/2,ex,ey};
    float round = 0.3;
    DrawRectangleRounded(rec,round,0,BEIGE);
    for (int i=0; i<60; i++)
    {
        double theta = i*2*PI/60;
        Vector2 endV, startV;
        if ((i >= 53 && i <= 59) || (i >= 0 && i <= 7))
        {
            if (i == 7 || i == 53)
            {
                startV.x = cx/2 + ex/2 - 9;
                double rad = (double) (startV.x - cx/2) / (cos(theta));
                startV.y = rad * sin(theta) + cy/2;
                endV.x = cx/2 + ex/2 + 5;
                rad = (double) (endV.x - cx/2) / (cos(theta));
                endV.y = rad * sin(theta) + cy/2;
            }
            else
            {
                startV.x = cx/2 + ex/2;
                double rad = (double) (startV.x - cx/2) / (cos(theta));
                startV.y = rad * sin(theta) + cy/2;
                endV.x = cx/2 + ex/2 + 15;
                rad = (double) (endV.x - cx/2) / (cos(theta));
                endV.y = rad * sin(theta) + cy/2;
            }
        }
        else if (i >= 8 && i <= 22)
        {
            if (i == 8 || i == 22)
            {
                startV.y = cy/2 + ey/2 - 9;
                double rad = (double) (startV.y - cy/2) / (sin(theta));
                startV.x = rad * cos(theta) + cx/2;
                endV.y = cy/2 + ey/2 + 5;
                rad = (double) (endV.y - cy/2) / (sin(theta));
                endV.x = rad * cos(theta) + cx/2;
            }
            else
            {
                startV.y = cy/2 + ey/2;
                double rad = (double) (startV.y - cy/2) / (sin(theta));
                startV.x = rad * cos(theta) + cx/2;
                endV.y = cy/2 + ey/2 + 15;
                rad = (double) (endV.y - cy/2) / (sin(theta));
                endV.x = rad * cos(theta) + cx/2;
            }
        }
        if (i >= 23 && i <= 37)
        {
            if (i == 37 || i == 23)
            {
                startV.x = cx/2 - ex/2 + 9;
                double rad = (double) (startV.x - cx/2) / (cos(theta));
                startV.y = rad * sin(theta) + cy/2;
                endV.x = cx/2 - ex/2 - 5;
                rad = (double) (endV.x - cx/2) / (cos(theta));
                endV.y = rad * sin(theta) + cy/2;
            }
            else
            {
                startV.x = cx/2 - ex/2;
                double rad = (double) (startV.x - cx/2) / (cos(theta));
                startV.y = rad * sin(theta) + cy/2;
                endV.x = cx/2 - ex/2 - 15;
                rad = (double) (endV.x - cx/2) / (cos(theta));
                endV.y = rad * sin(theta) + cy/2;
            }
        }
        else if (i >= 38 && i <= 52)
        {
            if (i == 38 || i == 52)
            {
                startV.y = cy/2 - ey/2 + 9;
                double rad = (double) (startV.y - cy/2) / (sin(theta));
                startV.x = rad * cos(theta) + cx/2;
                endV.y = cy/2 - ey/2 - 5;
                rad = (double) (endV.y - cy/2) / (sin(theta));
                endV.x = rad * cos(theta) + cx/2;
            }
            else
            {
                startV.y = cy/2 - ey/2;
                double rad = (double) (startV.y - cy/2) / (sin(theta));
                startV.x = rad * cos(theta) + cx/2;
                endV.y = cy/2 - ey/2 - 15;
                rad = (double) (endV.y - cy/2) / (sin(theta));
                endV.x = rad * cos(theta) + cx/2;
            }
        }
        if(i%15==0) DrawLineEx(startV, endV, 7, BLACK);
        else if (i%5==0) DrawLineEx(startV, endV, 4, BLUE);
        else DrawLineEx(startV, endV, 2, BLUE);
    }
    time_t t2 = time(NULL);
    struct tm *t = localtime(&t2);
    drawHourHand(cx/2, cy/2, radius, t -> tm_hour, t -> tm_min, t -> tm_sec);
    drawMinuteHand(cx/2, cy/2, radius, t -> tm_hour, t -> tm_min, t -> tm_sec);
    drawSecondHand(cx/2, cy/2, radius, t -> tm_hour, t -> tm_min, t -> tm_sec);
    DrawCircle(cx/2, cy/2, 8, BLACK);
    Vector2 origin;
    origin.x = 10;
    origin.y = 10;
    Rectangle rec2 = {cx/2,cy/2,20,20};
    double rotation =  6 * t->tm_sec;
    DrawRectanglePro(rec2, origin, rotation, RED);
        
}

int main(void)
{

    const int screenWidth = 450;
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

            drawClock(450, 450, 250, 350, 350);
            DrawText(timestr, x, y, fontSize, GREEN);
            if (IsKeyDown(KEY_ESCAPE)) WindowShouldClose();

        EndDrawing();
    }

    
    CloseWindow();        
    

    return 0;   
}