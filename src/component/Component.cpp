//
// Created by Sanjay on 7/19/2025.
//

#include "component/Component.h"

// public
Actor *Component::GetOwner() const { return actor; }
void Component::Input(const bool keys[]) { HandleInput(keys); }
void Component::Update(float deltaTime) { HandleUpdate(deltaTime); }

// protected
Component::Component(Actor *actor) { actor = actor; }

Component::~Component() {}
// private