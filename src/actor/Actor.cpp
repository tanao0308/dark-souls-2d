#include "actor/Actor.h"

// public
Transform &Actor::GetTransform() { return m_transform; }
const Transform &Actor::GetTransform() const { return m_transform; }

void Actor::Input(const bool keys[]) {
    for (auto comp : m_components) {
        comp->HandleInput(keys);
    }
    HandleInput(keys);
}
void Actor::Update(float deltaTime) {
    for (auto comp : m_components) {
        comp->Update(deltaTime);
    }
    HandleUpdate(deltaTime);
}

// protected
Actor::Actor() : m_transform() {}

Actor::~Actor() {
    for (auto comp : m_components) {
        delete comp;
    }
}
// private