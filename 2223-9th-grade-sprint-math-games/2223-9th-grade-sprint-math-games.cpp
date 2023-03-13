#include "raylib.h"

typedef struct
{
    float x;
    float y;
    float height;
    float width;
    Vector2 speed;
} Player;

// Global Variables Declaration

static int screenWidth = 800;
static int screenHeight = 450;

static Player player;


static void InitGame(void);        // Initialize game
static void UpdateGame(void);      // Update game (one frame)
static void DrawGame(Texture2D);        // Draw game (one frame)
static void UpdateDrawGame(void); // Update and Draw (one frame)

int main(void)
{
    InitWindow(screenWidth, screenHeight, "Binary Space");

    InitGame();

    SetTargetFPS(60);

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        UpdateDrawGame();

    }
    CloseWindow();

    return 0;
}

// Initialize game variables
void InitGame()
{
    player.x = screenWidth / 2.0f;
    player.y = screenHeight - 50;
    player.width = 20;
    player.height = 20;
    player.speed.x = 5;
    player.speed.y = 5;
}

//Update Game
void UpdateGame()
{
    // Player movement
    if (IsKeyDown(KEY_D))
        player.x += player.speed.x;
    if (IsKeyDown(KEY_A))
        player.x -= player.speed.x;
}

//Draw game
void DrawGame()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);
    Texture2D mainShip = LoadTexture("resources/images/main.png");
    //Main ship
    DrawTexture(mainShip, player.x, player.y, WHITE);

    //Stop drawing
    EndDrawing();
}

//Update and Draw
void UpdateDrawGame(void)
{
    UpdateGame();
    DrawGame();
}