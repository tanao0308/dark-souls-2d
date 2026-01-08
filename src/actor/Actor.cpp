//
// Created by Sanjay on 7/19/2025.
//

#include "actor/Actor.h"

// public
Transform &Actor::GetTransform() { return transform; }
const Transform &Actor::GetTransform() const { return transform; }

void Actor::Input(const bool keys[]) {
    for (auto cmp : mComponents) {
        cmp->HandleInput(keys);
    }
    HandleInput(keys);
}
void Actor::Update(float deltaTime) {
    for (auto cmp : mComponents) {
        cmp->Update(deltaTime);
    }
    HandleUpdate(deltaTime);
}

// protected
Actor::Actor() {}

Actor::~Actor() {
    for (auto comp : mComponents) {
        delete comp;
    }
}
// private