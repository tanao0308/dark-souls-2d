#include "utils/Transform.h"
#include "spdlog/spdlog.h"
#include "utils/Enums.h"
#include <iomanip>
#include <sstream>

// public
Transform::Transform() : m_rect({0, 0, 0, 0}) {}
Transform::~Transform() {}

std::string Transform::ToString() const {
    std::ostringstream ss;
    auto center = GetTileCenterPosition();
    auto size = GetTileSize();
    ss << std::fixed << std::setprecision(2);
    ss << "Transform["
       << "pos=(" << center.x << "," << center.y << "), "
       << "size=(" << size.x << "," << size.y << "), "
       << "rot=" << m_rotation << ", "
       << "layer=" << m_layer << "]";
    return ss.str();
}

SDL_FRect Transform::GetRealRect() const { return m_rect; }

Vector2 Transform::GetTileCenterPosition() const { return GetRealCenterPosition() * (1 / TILE_SIZE); }
void Transform::SetTileCenterPosition(const Vector2 &position) { SetRealCenterPosition(position * TILE_SIZE); }

Vector2 Transform::GetTileSize() const { return Vector2(m_rect.w / TILE_SIZE, m_rect.h / TILE_SIZE); }
void Transform::SetTileSize(const Vector2 &size) {
    auto center = GetRealCenterPosition();
    m_rect.w = size.x * TILE_SIZE;
    m_rect.h = size.y * TILE_SIZE;
    // 为保持中心点不变，更新坐标点（左上）
    SetRealCenterPosition(center);
}

float Transform::GetRotation() const {
    spdlog::debug("Transform::GetRotation()");
    return m_rotation;
}
void Transform::SetRotation(const float rotation) { m_rotation = rotation; }

int Transform::GetLayer() const { return m_layer; }
void Transform::SetLayer(const int layer) { m_layer = layer; }

Vector2 Transform::GetForward() const {
    // 原点在左上！
    return Vector2(Math::Cos(m_rotation), -Math::Sin(m_rotation));
}

Transform Transform::ToCameraTransform(const Transform &camera) const {
    return *this;
    spdlog::debug("Transform::ToCameraTransform()");
    // 以下逻辑有问题
    Transform res;
    res.m_rect = {m_rect.x - camera.m_rect.x, m_rect.y - camera.m_rect.y, m_rect.w, m_rect.h};
    res.m_rotation = m_rotation - camera.m_rotation;
    res.m_layer = m_layer - camera.m_layer;
    // 将相机坐标转化为屏幕左上原点坐标
    res.m_rect.x += WINDOW_WIDTH * TILE_SIZE / 2;
    res.m_rect.y += WINDOW_HEIGHT * TILE_SIZE / 2;
    return res;
}

// protected

// private
Vector2 Transform::GetRealCenterPosition() const { return Vector2(m_rect.x + m_rect.w / 2, m_rect.y + m_rect.h / 2); }
void Transform::SetRealCenterPosition(const Vector2 &position) {
    m_rect.x = position.x - m_rect.w / 2;
    m_rect.y = position.y - m_rect.h / 2;
}