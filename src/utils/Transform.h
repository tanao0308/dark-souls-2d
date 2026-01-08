//
// Created by Sanjay on 7/19/2025.
//

#pragma once
#include "SDL3/SDL_rect.h"
#include "utils/Math.h"

/*
游戏角色的物理状态信息
*/
class Transform {
  public:
    const Vector2 &GetPosition() const;
    void SetPosition(const Vector2 &position);
    const double &GetRotation() const;
    void SetRotation(const double &rotation);
    const double &GetScale() const;
    void SetScale(const double &scale);
    Vector2 GetForward() const;

  private:
    Vector2 position;
    double rotation = 0.0f; // 旋转
    double scale = 1.0f;    // 比例
};
