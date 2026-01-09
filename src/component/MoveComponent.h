#pragma once

#include "SDL3/SDL.h"
#include "component/Component.h"

class MoveComponent : public Component {
  public:
    void SetPosSpeed(float posSpeed);
    float GetPosSpeed();
    void SetRotSpeed(float rotSpeed);
    float GetRotSpeed();

  protected:
    friend class Actor;

    MoveComponent(class Actor *owner); // 防止在 Actor 外被创建
    ~MoveComponent();
    void HandleInput(const bool keys[]) override;
    void HandleUpdate(float deltaTime) override;

  private:
    float m_posSpeed = 0.0f;
    float m_rotSpeed = 0.0f;
};