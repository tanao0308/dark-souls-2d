#include "actor/Actor.h"
#include "utils/Enums.h"
#include "component/RenderComponent.h"

struct TilePos {
    float x, y; // 原点为地图的左上角，单位为单元格
    int layer;  // 当前所在层数
    TilePos(float x, float y, int layer = 0) : x(x), y(y), layer(layer);
};

class TileActor : public Actor {
  public:
    TilePos getTilePos();

  protected:
    friend class Game;

    RenderComponent *render = nullptr;
    TilePos tilePos; // 在地图上的位置
    TileType tileType;

    TileActor(TilePos tilePos, TileType tileType);
    void HandleInput(const bool keys[]) override;
    void HandleUpdate(float deltaTime) override;

  private:
};