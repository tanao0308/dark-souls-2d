#include "actor/Actor.h"
#include "component/RenderComponent.h"

class TileActor : public Actor {
  public:
  protected:
    friend class Game;

    RenderComponent *render = nullptr; // 贴图组件
    TileType tileType;

    // 常规函数
    TileActor(Vector2 tilePos, int layer, TileType tileType);
    ~TileActor();
    void HandleInput(const bool keys[]) override;
    void HandleUpdate(float deltaTime) override;

  private:
};