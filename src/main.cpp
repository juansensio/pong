#include <raylib.h>
#include "rlImGui.h"
#include "imgui.h"

#define RAYGUI_IMPLEMENTATION        // Define the implementation of raygui here
#include "raygui.h"                 // Include raygui after the implementation define

#include "raymath.h"

int main() {
    // Initialize window
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Raylib + ImGui Example");
    
    SetTargetFPS(60);               // Set target frames-per-second
    
    // Setup Dear ImGui
    rlImGuiSetup(true);

    // Variables for ImGui controls
    bool show_demo_window = true;
    float f = 0.0f;
    int counter = 0;
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Draw
        BeginDrawing();
            ClearBackground(WHITE);
            
            // Start ImGui frame
            rlImGuiBegin();
            
            // Create a simple ImGui window
            ImGui::Begin("Hello ImGui!");
            ImGui::Text("This is a sample text");
            ImGui::SliderFloat("Float slider", &f, 0.0f, 1.0f);
            if (ImGui::Button("Button"))
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);
            
            // Show ImGui demo window
            if (show_demo_window)
                ImGui::ShowDemoWindow(&show_demo_window);
                
            ImGui::End();
            
            // End ImGui frame
            rlImGuiEnd();
            
            // Your regular raylib drawing code can go here
            // DrawText("Welcome to Raylib + ImGui!", 190, 200, 20, LIGHTGRAY);

            GuiButton(Rectangle{ 10, 10, 100, 50 }, "Click me");
        EndDrawing();
    }

    // Cleanup
    rlImGuiShutdown();
    CloseWindow();                  // Close window and OpenGL context
    return 0;
}
