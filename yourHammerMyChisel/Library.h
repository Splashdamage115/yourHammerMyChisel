#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>

#define DEBUG_MSG(x) (std::cout << (x) << std::endl)

#define SCREEN_WIDTH 2048
#define SCREEN_HEIGHT 1536

#define MASK_WIDTH 11
#define WASK_HEIGHT 16

#define MASK_PIXEL_SIZE 24.f
#define MASK_PIXEL_OFFSET 1.f
#define MASK_START_X 1200.f
#define MASK_START_Y 450.f
#define MASK_SHADOW_OFFSET_X 8.f
#define MASK_SHADOW_OFFSET_Y 6.f

#define MAX_WRONG_PERCENT 0.2f