#include "pch.h"

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Binary Space12");
    mainMenu(screenWidth, screenHeight);
    SetTargetFPS(60);


    Player player;
    Enemy enemy[MAX_ENEMIES];
    Zeros zero[NUM_SHOOTS];
    Ones one[NUM_SHOOTS];
    Equation equation;

    int shootRate = 0;
    int shootRate1 = 0;

    bool playing = false;
    int activeEnemies = 1;

    std::string binary1 = generateRandomBinaryString();
    std::string binary2 = generateRandomBinaryString();
    std::string playerAnswer;

    int level = 1;
    int enemiesKilled = 0;

    //Load Texture
    Texture2D mainShip = LoadTexture("resources/images/main.png");
    Texture2D enemyShip = LoadTexture("resources/images/enemy.png");

    //Initialize player
    player.x = screenWidth / 2.0f;
    player.y = screenHeight - 50;
    player.width = 20;
    player.height = 20;
    player.speed.x = 5;
    player.speed.y = 5;

    //Random equation
    GenerateRandomEquation(equation, binary1, binary2, level);

    // Initialize enemies
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        enemy[i].width = 125;
        enemy[i].height = 124;
        enemy[i].x = GetRandomValue(0, screenWidth);
        enemy[i].y = GetRandomValue(-screenHeight, -20);
        enemy[i].speed.x = 5;
        enemy[i].speed.y = 2;
        enemy[i].active = true;
    }
    // Initialize shots of type zero
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
    // Initialize shots of type one
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
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update and Draw
            //Load Textures
        if (!playing)
        {
            // Update

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
                        binary1 = generateRandomBinaryString();
                        binary2 = generateRandomBinaryString();
                        enemy[i].x = GetRandomValue(0, screenWidth);
                        enemy[i].y = GetRandomValue(-screenHeight, -20);
                        GenerateRandomEquation(equation, binary1, binary2, level);
                        playerAnswer = "";
                    }
                    if (playerAnswer == equation.answer1)
                    {
                        binary1 = generateRandomBinaryString();
                        binary2 = generateRandomBinaryString();
                        enemy[i].x = GetRandomValue(0, screenWidth);
                        enemy[i].y = GetRandomValue(-screenHeight, -20);
                        GenerateRandomEquation(equation, binary1, binary2, level);
                        playerAnswer = "";
                        enemiesKilled++;
                    }
                }
            }
            if (enemiesKilled == 5)
            {
                enemiesKilled = 0;
                level++;
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


            //Draw Game
            BeginDrawing();

            ClearBackground(RAYWHITE);
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
                switch (level)
                {
                case 1:
                    if (equation.Operator == "&" || equation.Operator == "|" || equation.Operator == "^")
                    {
                        DrawText(TextFormat("%s %s %s = ", binary1.c_str(), equation.Operator.c_str(), binary2.c_str()), (enemy[i].x + 10), (enemy[i].y + 15), 30, BLACK);
                    }
                    else
                    {
                        DrawText(TextFormat("%s %s %i = ", binary1.c_str(), equation.Operator.c_str(), 2), (enemy[i].x + 10), (enemy[i].y + 15), 30, BLACK);
                    }
                    break;
                case 2:
                    if ((equation.Operator == "&") || (equation.Operator == "|") || (equation.Operator == "^"))
                    {
                        DrawText(TextFormat("%s %s %s = ", std::to_string(equation.num1).c_str(), equation.Operator.c_str(), std::to_string(equation.num2).c_str()), (enemy[i].x + 10), (enemy[i].y + 15), 30, BLACK);
                    }
                    if ((equation.Operator3 == "<<") || (equation.Operator3 == ">>"))
                    {
                        DrawText(TextFormat("%s %s %i = ", std::to_string(equation.num1).c_str(), equation.Operator.c_str(), 2), (enemy[i].x + 10), (enemy[i].y + 15), 30, BLACK);
                    }
                    if ((equation.Operator3 == "~"))
                    {
                        DrawText(TextFormat("%s %s = ", equation.Operator.c_str(), std::to_string(equation.num1).c_str()), (enemy[i].x + 10), (enemy[i].y + 15), 30, BLACK);
                    }
                    break;
                case 3:
                    if ((equation.Operator == "&") || (equation.Operator == "|") || (equation.Operator == "^"))
                    {
                        DrawText(TextFormat("(%s %s %s) %s", std::to_string(equation.num1).c_str(), equation.Operator.c_str(), std::to_string(equation.num2).c_str(), equation.Operator2.c_str()), (enemy[i].x), (enemy[i].y - 50), 30, BLACK);
                        if ((equation.Operator3 == "&") || (equation.Operator3 == "|") || (equation.Operator3 == "^"))
                        {
                            DrawText(TextFormat("(%s %s %s)", std::to_string(equation.num3).c_str(), equation.Operator3.c_str(), std::to_string(equation.num4).c_str()), (enemy[i].x + 150), (enemy[i].y - 50), 30, BLACK);
                        }
                        if ((equation.Operator3 == "<<") || (equation.Operator3 == ">>"))
                        {
                            DrawText(TextFormat("(%s %s %i)", std::to_string(equation.num3).c_str(), equation.Operator3.c_str(), 2), (enemy[i].x + 150), (enemy[i].y - 50), 30, BLACK);
                        }
                        if (equation.Operator3 == "~")
                        {
                            DrawText(TextFormat("(%s %s)", equation.Operator3.c_str(), std::to_string(equation.num4).c_str()), (enemy[i].x + 150), (enemy[i].y), 30, BLACK);
                        }
                    }


                    if ((equation.Operator == "<<") || (equation.Operator == ">>"))
                    {
                        DrawText(TextFormat("(%s %s %i) %s", std::to_string(equation.num1).c_str(), equation.Operator2.c_str(), 2, equation.Operator2.c_str()), (enemy[i].x), (enemy[i].y - 50), 30, BLACK);
                        if ((equation.Operator3 == "<<") || (equation.Operator3 == ">>"))
                        {
                            DrawText(TextFormat("(%s %s %i)", std::to_string(equation.num3).c_str(), equation.Operator3.c_str(), 2), (enemy[i].x + 150), (enemy[i].y - 50), 30, BLACK);
                        }
                        if ((equation.Operator3 == "&") || (equation.Operator3 == "|") || (equation.Operator3 == "^"))
                        {
                            DrawText(TextFormat("(%s %s %s)", std::to_string(equation.num3).c_str(), equation.Operator3.c_str(), std::to_string(equation.num4).c_str()), (enemy[i].x + 150), (enemy[i].y - 50), 30, BLACK);
                        }
                        if (equation.Operator3 == "~")
                        {
                            DrawText(TextFormat("(%s %s)", equation.Operator3.c_str(), std::to_string(equation.num4).c_str()), (enemy[i].x + 150), (enemy[i].y - 50), 30, BLACK);
                        }
                    }


                    if ((equation.Operator == "~"))
                    {
                        DrawText(TextFormat("(%s %s)", equation.Operator.c_str(), std::to_string(equation.num1).c_str()), (enemy[i].x), (enemy[i].y - 50), 30, BLACK);
                        if (equation.Operator3 == "~")
                        {
                            DrawText(TextFormat("(%s %s)", equation.Operator3.c_str(), std::to_string(equation.num4).c_str()), (enemy[i].x + 150), (enemy[i].y - 50), 30, BLACK);
                        }
                        if ((equation.Operator3 == "<<") || (equation.Operator3 == ">>"))
                        {
                            DrawText(TextFormat("(%s %s %i)", std::to_string(equation.num3).c_str(), equation.Operator3.c_str(), 2), (enemy[i].x + 150), (enemy[i].y - 50), 30, BLACK);
                        }
                        if ((equation.Operator3 == "&") || (equation.Operator3 == "|") || (equation.Operator3 == "^"))
                        {
                            DrawText(TextFormat("(%s %s %s)", std::to_string(equation.num3).c_str(), equation.Operator3.c_str(), std::to_string(equation.num4).c_str()), (enemy[i].x + 150), (enemy[i].y - 50), 30, BLACK);
                        }
                    }

                }
            }
            DrawText(equation.answer1.c_str(), 10, 10, 30, BLACK);
            //Stop drawing
            EndDrawing();
        }

    }
}
