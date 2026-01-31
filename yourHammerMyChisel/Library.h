#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>

#define DEBUG_MSG(x) (std::cout << (x) << std::endl)

#define SCREEN_WIDTH 2048
#define SCREEN_HEIGHT 1536

#define LEFT_MIN 900
#define STAND_X 300.f

#define MINI_MASK_SIZE 32

#define MASK_WIDTH 8
#define WASK_HEIGHT 10

#define MASK_PIXEL_SIZE 96.f
#define MASK_PIXEL_OFFSET 0.f
#define MASK_START_X 1200.f
#define MASK_START_Y 450.f
#define MASK_SHADOW_OFFSET_X 8.f
#define MASK_SHADOW_OFFSET_Y 6.f

#define MAX_WRONG_PERCENT 0.2f

#define PAGE_PIXEL_SIZE 8.f
#define PAGE_SIZE_X 64
#define PAGE_SIZE_Y 108
#define PAGE_START_X 1200.f
#define PAGE_START_Y 250.f

#define TEXT_LETTER_DELAY 0.05f

#define MAX_DAYS 2