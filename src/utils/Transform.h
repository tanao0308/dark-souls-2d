#pragma once
#include "SDL3/SDL_rect.h"
#include "utils/Math.h"
#include <string>

// 游戏角色的物理状态信息
// 不把原始单位暴露出去！
class Transform {
  public:
    Transform();
    ~Transform();
    std::string ToString() const;
    // 获取当前矩形
    SDL_FRect GetRealRect() const;
    // 用TILE_SIZE GET/SET中心位置
    Vector2 GetTileCenterPosition() const;
    void SetTileCenterPosition(const Vector2 &position);
    // 设置大小
    Vector2 GetTileSize() const;
    void SetTileSize(const Vector2 &size);
    // 设置旋转
    float GetRotation() const;
    void SetRotation(const float rotation);
    // 设置层数
    int GetLayer() const;
    void SetLayer(const int layer);
    // 获取当前方向向量
    Vector2 GetForward() const;
    // 获取经过镜头变换后的Transform
    Transform ToCameraTransform(const Transform &camera) const;

  private:
    // 单位都是原始单位，非 TILE_SIZE，外部全部使用 TILE_SIZE
    SDL_FRect m_rect;        // 以左上角为坐标的位置+宽高
    float m_rotation = 0.0f; // 旋转
    int m_layer = 0;         // 当前层数

    // 用原始单位GET/SET中心位置
    Vector2 GetRealCenterPosition() const;
    void SetRealCenterPosition(const Vector2 &position);
};