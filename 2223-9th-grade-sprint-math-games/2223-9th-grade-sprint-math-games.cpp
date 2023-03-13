#include "raylib.h"

typedef struct
{
    float x;
    float y;
    float height;
    float width;
    Vector2 speed;
} Player;

typedef struct
{
    float x;
    float y;
    float height;
    float width;
    Vector2 speed;
    bool active;
} Enemy;

//Defines 
#define MAX_ENEMIES 3
// Global Variables Declaration

static int screenWidth = 800;
static int screenHeight = 450;

static Player player;
static Enemy enemy[MAX_ENEMIES];

static int activeEnemies = 3;
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

    // Initialize enemies
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        enemy[i].width = 125;
        enemy[i].height = 124;
        enemy[i].x = GetRandomValue(0, screenWidth);
        enemy[i].y = GetRandomValue(-screenHeight, -20);
        enemy[i].speed.x = 5;
        enemy[i].speed.y = 5;
        enemy[i].active = true;
    }
}

//Update Game
void UpdateGame()
{
    // Player movement
    if (IsKeyDown(KEY_D))
        player.x += player.speed.x;
    if (IsKeyDown(KEY_A))
        player.x -= player.speed.x;

    //Enemy behaviour
    for (int i = 0; i < activeEnemies; i++)
    {
        if (enemy[i].active)
        {
            enemy[i].y += enemy[i].speed.y;

            if (enemy[i].y > screenHeight)
            {
                enemy[i].x = GetRandomValue(0, screenWidth);
                enemy[i].y = GetRandomValue(-screenHeight, -20);
            }
        }
    }
}

//Draw game
void DrawGame()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);
    Texture2D mainShip = LoadTexture("resources/images/main.png");
    Texture2D enemyShip = LoadTexture("resources/images/enemy.png");
    //Main ship
    DrawTexture(mainShip, player.x, player.y, WHITE);

    for (int i = 0; i < activeEnemies; i++)
    {
        if (enemy[i].active)
            DrawTexture(enemyShip, enemy[i].x, enemy[i].y, WHITE);
    }
    //Stop drawing
    EndDrawing();
}

//Update and Draw
void UpdateDrawGame(void)
{
    UpdateGame();
    DrawGame();
}