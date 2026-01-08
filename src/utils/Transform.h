#pragma once
#include "SDL3/SDL_rect.h"
#include "utils/Math.h"

// 游戏角色的物理状态信息
// 不把原始单位暴露出去！
class Transform {
  public:
    Transform();
    ~Transform();
    // 用TILE_SIZE GET/SET中心位置
    const Vector2 &GetTileCenterPosition() const;
    void SetTileCenterPosition(const Vector2 &position);
    // 设置大小
    const Vector2 &GetTileSize() const;
    void SetTileSize(const Vector2 &size);
    // 设置旋转
    const double &GetRotation() const;
    void SetRotation(const double &rotation);
    // 设置层数
    const double &GetLayer() const;
    void SetLayer(const double &layer);
    // 获取当前方向向量
    Vector2 GetForward() const;
    // 获取经过镜头变换后的Transform
    Transform GetCameraTransform(Transform &camera) const;

  private:
    // 单位都是原始单位，非 TILE_SIZE，外部全部使用 TILE_SIZE
    SDL_FRect m_rect;         // 以左上角为坐标的位置+宽高
    double m_rotation = 0.0f; // 旋转
    int m_layer = 0;          // 当前层数

    // 获取当前矩形
    SDL_FRect GetRealRect(Vector2 size) const;
    // 用原始单位GET/SET中心位置
    const Vector2 &GetRealCenterPosition() const;
    void SetRealCenterPosition(const Vector2 &position);
};