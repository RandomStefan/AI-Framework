#pragma once

#define _USE_MATH_DEFINES

#include <math.h>

constexpr int ScreenWidth = 1280;
constexpr int ScreenHeight = 720;
constexpr int MaxBoids = 10;
constexpr float MaxBoidSpeed = 10.0f;
constexpr int MaxCellWidth = 32;
constexpr int MaxCellHeight = 32;

constexpr double RadToDeg = 180 / M_PI;
constexpr double DegToRad = M_PI / 180;