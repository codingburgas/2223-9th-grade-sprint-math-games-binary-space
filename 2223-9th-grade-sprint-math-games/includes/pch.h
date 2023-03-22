#pragma once
#include "raylib.h"
#include <string>
#include "equation.h"
#include "mainMenu.h"
#include "bitwiseOperators.h"

//Defines 
#define MAX_ENEMIES 3
#define NUM_SHOOTS 50

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