// TileMap.h
#pragma once
#include "actor/TileActor.h"
#include "core/Game.h"
#include <vector>

class TileMap {
  protected:
    friend Game;
    TileMap(int width, int height, int layers = 1);
    ~TileMap();

    void GenerateTiles(); // 创建 TileActor
    TileActor *GetTileAt(int x, int y, int layer = 0) const;
    bool IsWalkable(int x, int y, int layer = 0) const;

    void AddToGame(class Game *game); // 把所有 TileActor 注册到 Game

  private:
    int width_;
    int height_;
    int layers_;
    std::vector<std::vector<std::vector<TileActor *>>> tiles_; // 3D数组 [layer][y][x]
};
