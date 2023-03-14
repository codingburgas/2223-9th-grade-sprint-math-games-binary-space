#include "raylib.h"

struct Player
{
    float x;
    float y;
    float height;
    float width;
    Vector2 speed;
};

struct Enemy
{
    float x;
    float y;
    float height;
    float width;
    Vector2 speed;
    bool active;
};
struct Zeros
{
    Rectangle rect;
    Vector2 speed;
    bool active;
};
struct Ones
{
    Rectangle rect;
    Vector2 speed;
    bool active;
};

//Defines 
#define MAX_ENEMIES 3
#define NUM_SHOOTS 50
// Global Variables Declaration

static int screenWidth = 800;
static int screenHeight = 450;

static Player player;
static Enemy enemy[MAX_ENEMIES];
static Zeros zero[NUM_SHOOTS];
static Ones one[NUM_SHOOTS];

static int shootRate;
static int shootRate1;

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
    activeEnemies = 1;
    shootRate = 0;

    //Initialize player
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
    // Initialize shoots of type zero
    for (int i = 0; i < NUM_SHOOTS; i++)
    {
        zero[i].rect.x = player.x;
        zero[i].rect.y = player.y + player.height / 4;
        zero[i].rect.width = 5;
        zero[i].rect.height = 5;
        zero[i].speed.x = 0;
        zero[i].speed.y = -10;
        zero[i].active = false;
    }
    // Initialize shoots of type one
    for (int i = 0; i < NUM_SHOOTS; i++)
    {
        one[i].rect.width = 5;
        one[i].rect.height = 10;
        one[i].rect.x = player.x;
        one[i].rect.y = player.y + player.height / 4;
        one[i].speed.x = 0;
        one[i].speed.y = -10;
        one[i].active = false;
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

    if (IsKeyDown(KEY_ZERO))
    {
        shootRate += 5;
        for (int i = 0; i < NUM_SHOOTS; i++)
        {
            if (!zero[i].active && shootRate % 40 == 0)
            {
                zero[i].rect.x = player.x;
                zero[i].rect.y = player.y + player.height / 4;
                zero[i].active = true;
                break;
            }
        }
    }
    else if (IsKeyDown(KEY_ONE))
    {
        shootRate1 += 5;
        for (int i = 0; i < NUM_SHOOTS; i++)
        {
            if (!one[i].active && shootRate1 % 40 == 0)
            {
                one[i].rect.x = player.x;
                one[i].rect.y = player.y + player.height / 4;
                one[i].active = true;
                break;
            }
        }
    }

    for (int i = 0; i < NUM_SHOOTS; i++)
    {
        if (zero[i].active)
        {
            // Movement
            zero[i].rect.y += zero[i].speed.y;

            for (int j = 0; j < activeEnemies; j++)
            {
                if (enemy[j].active)
                {
                    if (zero[i].rect.y <= 0) //goes above the screen
                    {
                        zero[i].active = false;
                        shootRate = 0;
                    }
                }
            }
        }
    }
    for (int i = 0; i < NUM_SHOOTS; i++)
    {
        if (one[i].active)
        {
            one[i].rect.y += one[i].speed.y;
            for (int j = 0; j < activeEnemies; j++)
            {
                if (enemy[j].active)
                {
                    if (one[i].rect.y <= 0) //goes above the screen
                    {
                        one[i].active = false;
                        shootRate1 = 0;
                    }
                }
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
    for (int i = 0; i < NUM_SHOOTS; i++)
    {
        if (zero[i].active)
            DrawText("0", zero[i].rect.x, zero[i].rect.y, 10, BLACK);
    }
    for (int i = 0; i < NUM_SHOOTS; i++)
    {
        if (one[i].active)
            DrawText("1", one[i].rect.x, one[i].rect.y, 10, BLACK);
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