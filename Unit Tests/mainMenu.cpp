#include "pch.h"
bool mainMenu(const int screenWidth, const int screenHeight)
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
            return 1;
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
