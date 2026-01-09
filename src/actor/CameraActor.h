#pragma once

#include "actor/Actor.h"
#include "actor/PlayerActor.h"
#include "component/MoveComponent.h"
#include "utils/Enums.h"

class CameraActor : public Actor {
  protected:
    friend class Game;

    CameraActor(PlayerActor *player);
    ~CameraActor();
    void HandleInput(const bool keys[]) override;
    void HandleUpdate(float deltaTime) override;

  private:
    PlayerActor *m_player = nullptr;
};