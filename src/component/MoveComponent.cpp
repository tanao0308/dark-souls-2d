//
// Created by Sanjay on 7/19/2025.
//

#include "component/MoveComponent.h"
#include "actor/Actor.h"
#include "utils/Math.h"

// public
void MoveComponent::SetPosSpeed(float posSpeed) { posSpeed = posSpeed; }
float MoveComponent::GetPosSpeed() { return posSpeed; }
void MoveComponent::SetRotSpeed(float rotSpeed) { rotSpeed = rotSpeed; }
float MoveComponent::GetRotSpeed() { return rotSpeed; }
// protected
MoveComponent::MoveComponent(class Actor *owner) : Component(owner) {}
MoveComponent::~MoveComponent() {}
void MoveComponent::HandleInput(const bool keys[]) {}

void MoveComponent::HandleUpdate(float deltaTime) {
    auto &tran = actor->GetTransform();
    auto deltaRot = rotSpeed * deltaTime;
    tran.SetRotation(tran.GetRotation() + deltaRot);
    auto deltaPos = tran.GetForward() * posSpeed * deltaTime;
    tran.SetPosition(tran.GetPosition() + deltaPos);
}