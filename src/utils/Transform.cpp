//
// Created by Sanjay on 7/19/2025.
//

#include "utils/Transform.h"

const Vector2 &Transform::GetPosition() const { return position; }

void Transform::SetPosition(const Vector2 &position) { position = position; }

const double &Transform::GetRotation() const { return rotation; }
void Transform::SetRotation(const double &rotation) { rotation = rotation; }
const double &Transform::GetScale() const { return scale; }
void Transform::SetScale(const double &scale) { scale = scale; }
Vector2 Transform::GetForward() const {
    // 原点在左上！
    return Vector2(Math::Cos(rotation), -Math::Sin(rotation));
}