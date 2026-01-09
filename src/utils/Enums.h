#pragma once

const bool DEBUG = true;

static constexpr float WINDOW_WIDTH = 160.0F;
static constexpr float WINDOW_HEIGHT = 120.0f;
static constexpr float TILE_SIZE = 5.0f;

// Actor 渲染顺序枚举类
enum class RenderOrder { // 从小到大进行渲染
    NONE,
    MAP,
    PLAYER,
};

// Tile 种类
enum class TileType { Solid, Hole };