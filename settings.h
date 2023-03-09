#pragma once

static constexpr int WIDTH = 3200;
static constexpr int HEIGHT = 1600;
static constexpr int FPS = 60;
static constexpr int CELL_SIZE = 100;
static constexpr int NUM_HORIZONTAL_CELLS = WIDTH/CELL_SIZE;
static constexpr int NUM_VERTICAL_CELLS = HEIGHT/CELL_SIZE;
static constexpr int NUM_BOIDS = 301;
static constexpr int OUT_OF_BOUNDS_SIZE = 200;
static constexpr float KEEP_IN_BOUNDS_FORCE = 0.15;
static constexpr int VISUAL_RANGE = 100;
static constexpr int SEPERATION_DISTANCE = 35;
static constexpr float TRIANGLE_HEIGHT = 16;
static constexpr float TRIANGLE_WIDTH = 7;
static constexpr float MAX_SPEED = 8.00f;
static constexpr float MIN_SPEED = 5.00f;
static constexpr float MAX_FORCE = 0.20f;