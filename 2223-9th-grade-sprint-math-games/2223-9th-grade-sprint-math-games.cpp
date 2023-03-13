#include "raylib.h"

static void InitGame(void);        // Initialize game
static void UpdateGame(void);      // Update game (one frame)
static void DrawGame(void);        // Draw game (one frame)
static void UpdateDrawGame(void); // Update and Draw (one frame)

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Binary Space");
    SetTargetFPS(60);
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        BeginDrawing();

        UpdateDrawGame();

        EndDrawing();
    }
    CloseWindow();

    return 0;
}

// Initialize game variables
void InitGame()
{

}

//Update Game
void UpdateGame()
{

}

//Draw game
void DrawGame()
{

}

//Update and Draw
void UpdateDrawGame()
{
    void DrawGame();
    void UpdateGame();
}