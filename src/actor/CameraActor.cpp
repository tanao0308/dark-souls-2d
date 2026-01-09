#include "actor/CameraActor.h"
#include "spdlog/spdlog.h"

// public

// protected
CameraActor::CameraActor(PlayerActor *player) : m_player(player) {
    spdlog::debug("CameraActor::CameraActor()");
    if (!m_player) {
        spdlog::debug("m_player is null!");
    }
}
CameraActor::~CameraActor() {}
void CameraActor::HandleInput(const bool keys[]) {}
void CameraActor::HandleUpdate(float deltaTime) {
    spdlog::debug("CameraActor::HandleUpdate()");
    m_transform = m_player->GetTransform();
}

// private