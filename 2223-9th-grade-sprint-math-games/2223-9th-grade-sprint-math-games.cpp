#include "raylib.h"
#include <string>
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
struct Equation
{
    int num1 = 0;
    int num2 = 0;
    char Operator = 0;
    int answer = 0;
};

//Defines 
#define MAX_ENEMIES 3
#define NUM_SHOOTS 50
// Global Variables Declaration

static int screenWidth = 1280;
static int screenHeight = 720;

static Player player;
static Enemy enemy[MAX_ENEMIES];
static Zeros zero[NUM_SHOOTS];
static Ones one[NUM_SHOOTS];
static Equation equation;

static int shootRate;
static int shootRate1;

static bool playing = false;
static int activeEnemies = 3;

static std::string playerAnswer;
static void InitGame();        // Initialize game
static void UpdateGame();      // Update game (one frame)
static void DrawGame();        // Draw game (one frame)
static void UpdateDrawGame(); // Update and Draw (one frame)
static Equation GenerateRandomEquation();
static bool mainMenu();

int main()
{
    InitWindow(screenWidth, screenHeight, "Binary Space12");
    mainMenu();
    // Initialize audio device
    InitAudioDevice();

    InitGame();

    SetTargetFPS(60);
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update and Draw
        if (!playing)
        {
            UpdateDrawGame();
        }
    }

}

// Initialize game variables
void InitGame()
{
    //Shooting
    activeEnemies = 1;
    shootRate = 0;
    shootRate1 = 0;

    //Random equation
    equation = GenerateRandomEquation();
    equation.answer = 010011;

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
        enemy[i].speed.y = 0.3;
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

    //Walls
    if (player.x <= 0)
        player.x = 0;
    if (player.x + player.width >= screenWidth)
        player.x = screenWidth - player.width;

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
                equation = GenerateRandomEquation();
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

    // Shoot logic for zero
    for (int i = 0; i < NUM_SHOOTS; i++)
    {
        Rectangle EnemyRec = { enemy[i].x, enemy[i].y, enemy[i].width, enemy[i].height };
        if (zero[i].active)
        {
            // Movement
            zero[i].rect.y += zero[i].speed.y;

            // Collision with enemy
            for (int j = 0; j < activeEnemies; j++)
            {
                if (enemy[j].active)
                {
                    if (CheckCollisionRecs(zero[i].rect, EnemyRec))
                    {
                        zero[i].active = false;
                        playerAnswer += '0';
                        shootRate = 0;
                        // enemiesKill++;
                        // score += 100;
                    }

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
        Rectangle EnemyRec = { enemy[i].x, enemy[i].y, enemy[i].width, enemy[i].height };
        if (one[i].active)
        {
            one[i].rect.y += one[i].speed.y;
            for (int j = 0; j < activeEnemies; j++)
            {
                if (enemy[j].active)
                {
                    if (CheckCollisionRecs(one[i].rect, EnemyRec))
                    {
                        one[i].active = false;
                        playerAnswer += '1';
                        shootRate1 = 0;

                        // enemiesKill++;
                        // score += 100;
                    }

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
    for (int i = 0; i < activeEnemies; i++)
    {
        DrawText(TextFormat("%i %c %i = ", equation.num1, equation.Operator, equation.num2), (enemy[i].x + 10), (enemy[i].y + 15), 30, BLACK);
    }
    //Stop drawing
    EndDrawing();
}

Equation GenerateRandomEquation()
{
    Equation equation;

    //Equation
    equation.Operator = GetRandomValue(0, 4);
    equation.num1 = GetRandomValue(1, 10);
    equation.num2 = GetRandomValue(1, 10);

    switch (equation.Operator)
    {
    case 0:
        equation.answer += (equation.num1 & equation.num2);
        equation.Operator = '&';
        break;
    case 1:
        equation.answer += (equation.num1 | equation.num2);
        equation.Operator = '|';
        break;
    case 2:
        equation.answer += (equation.num1 ^ equation.num2);
        equation.Operator = '^';
        break;
    case 3:
        equation.answer += (equation.num1 << equation.num2);
        equation.Operator = '<<';
        break;
    case 4:
        equation.answer += (equation.num1 >> equation.num2);
        equation.Operator = '>>';
        break;
    }
    return equation;
}
bool mainMenu()
{
    Rectangle playButton = { screenWidth / 2 - 50, screenHeight / 2 - 40, 100, 30 };
    Rectangle quitButton = { screenWidth / 2 - 50, screenHeight / 2 + 20, 100, 30 };

    while (!WindowShouldClose())
    {
        // Check if the mouse is over the buttons
        bool playButtonHovered = CheckCollisionPointRec(GetMousePosition(), playButton);
        bool quitButtonHovered = CheckCollisionPointRec(GetMousePosition(), quitButton);

        // Check if the buttons are clicked
        if (playButtonHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            return true;
        }

        if (quitButtonHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            break;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the buttons
        DrawRectangleRec(playButton, playButtonHovered ? GRAY : LIGHTGRAY);
        DrawRectangleRec(quitButton, quitButtonHovered ? GRAY : LIGHTGRAY);

        DrawText("Play", playButton.x + 25, playButton.y + 8, 10, DARKGRAY);
        DrawText("Quit", quitButton.x + 25, quitButton.y + 8, 10, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
}
//Update and Draw
void UpdateDrawGame(void)
{
    UpdateGame();
    DrawGame();
}