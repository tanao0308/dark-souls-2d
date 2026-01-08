#include "utils/Transform.h"
#include "utils/Enums.h"

// public
Transform::Transform() : m_rect({0, 0, 0, 0}) {}
Transform::~Transform() {}

const Vector2 &Transform::GetTileCenterPosition() const { return GetRealCenterPosition() / TILE_SIZE; }
void Transform::SetTileCenterPosition(const Vector2 &position) { SetRealCenterPosition(position * TILE_SIZE); }

const Vector2 &Transform::GetTileSize() const { return Vector2(m_rect.x / TILE_SIZE, m_rect.y / TILE_SIZE); }
void Transform::SetTileSize(const Vector2 &size) {
    m_rect.x = size.x * TILE_SIZE;
    m_rect.y = size.y * TILE_SIZE;
}

const double &Transform::GetRotation() const { return m_rotation; }
void Transform::SetRotation(const double &rotation) { m_rotation = rotation; }

const double &Transform::GetLayer() const { return m_layer; }
void Transform::SetLayer(const double &layer) { m_layer = layer; }

Vector2 Transform::GetForward() const {
    // 原点在左上！
    return Vector2(Math::Cos(rotation), -Math::Sin(rotation));
}

Transform Transform::GetCameraTransform(const Transform &camera) const {
    Transform res;
    res.m_rect = {m_rect.x - camera.m_rect.x, m_rect.y - camera.m_rect.y, m_rect.w, m_rect.h};
    res.m_rotation = m_rotation - camera.m_rotation;
    res.m_layer = m_layer - camera.m_layer;
    return res;
}

// protected

// private
SDL_FRect Transform::GetRealRect(Vector2 size) const { return rect; }

const Vector2 &Transform::GetRealCenterPosition() const {
    return Vector2(m_rect.x + m_rect.w / 2, m_rect.y + m_rect.h / 2);
}
void Transform::SetRealCenterPosition(const Vector2 &position) {
    m_rect.x = position.x - m_rect.w / 2;
    m_rect.y = position.y - m_rect.h / 2;
}