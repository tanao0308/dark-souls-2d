//
// Created by Sanjay on 7/19/2025.
//

#include "component/MoveComponent.h"
#include "actor/Actor.h"
#include "spdlog/spdlog.h"
#include "utils/Math.h"

// public
void MoveComponent::SetPosSpeed(float posSpeed) { m_posSpeed = posSpeed; }
float MoveComponent::GetPosSpeed() { return m_posSpeed; }
void MoveComponent::SetRotSpeed(float rotSpeed) { m_rotSpeed = rotSpeed; }
float MoveComponent::GetRotSpeed() { return m_rotSpeed; }
// protected
MoveComponent::MoveComponent(class Actor *owner) : Component(owner) {}
MoveComponent::~MoveComponent() {}
void MoveComponent::HandleInput(const bool keys[]) { spdlog::debug("MoveComponent::HandleInput()"); }

void MoveComponent::HandleUpdate(float deltaTime) {
    spdlog::debug("MoveComponent::HandleUpdate()");
    auto &tran = m_actor->GetTransform();
    auto deltaRot = m_rotSpeed * deltaTime;
    tran.SetRotation(tran.GetRotation() + deltaRot);
    auto deltaPos = tran.GetForward() * m_posSpeed * deltaTime;
    tran.SetTileCenterPosition(tran.GetTileCenterPosition() + deltaPos);
}