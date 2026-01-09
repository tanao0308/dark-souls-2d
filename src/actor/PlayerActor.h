#pragma once

#include "actor/Actor.h"
#include "actor/TileActor.h"
#include "component/MoveComponent.h"
#include "component/RenderComponent.h"

class PlayerActor : public Actor {
  public:
  protected:
    friend class Game;

    PlayerActor();
    ~PlayerActor();
    void HandleInput(const bool keys[]) override;
    void HandleUpdate(float deltaTime) override;
    void SetTarget(Actor *actor);
    Actor *GetTarget();

  private:
    const float kPosSpeed = 30;            // 移速
    const float kRotSpeed = Math::Pi / 2;  // 转向速度
    const Vector2 kSize;                   // 大小
    const float kRotation = -Math::Pi / 2; // 人物朝向（不会改变，只改镜头方向）

    RenderComponent *m_render = nullptr;
    MoveComponent *m_move = nullptr;
};