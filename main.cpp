#include <raylib.h>

int main() {
    // Initialize window
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Raylib Example");
    
    SetTargetFPS(60);               // Set target frames-per-second
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Draw
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Welcome to Raylib!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();                  // Close window and OpenGL context
    return 0;
}