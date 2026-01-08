#include "actor/CameraActor.h"

// public

// protected
CameraActor::CameraActor(PlayerActor *player) : m_player(player) {}
CameraActor::~CameraActor() {}
void CameraActor::HandleInput(const bool keys[]) {}
void CameraActor::HandleUpdate(float deltaTime) { transform = m_player->GetTransform(); }

// private