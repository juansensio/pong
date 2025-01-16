#include <raylib.h>

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Pong");
    SetTargetFPS(60);               
    while (!WindowShouldClose())   
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Hola Mundo!", screenWidth/2 - MeasureText("Hola Mundo!", 20)/2, screenHeight/2 - 10, 20, WHITE);
        EndDrawing();
    }
    CloseWindow();                  
    return 0;
}
