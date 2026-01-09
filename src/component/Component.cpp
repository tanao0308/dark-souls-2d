//
// Created by Sanjay on 7/19/2025.
//

#include "component/Component.h"

// public
Actor *Component::GetOwner() const { return m_actor; }
void Component::Input(const bool keys[]) { HandleInput(keys); }
void Component::Update(float deltaTime) { HandleUpdate(deltaTime); }

// protected
Component::Component(Actor *actor) { m_actor = actor; }

Component::~Component() {}
// private