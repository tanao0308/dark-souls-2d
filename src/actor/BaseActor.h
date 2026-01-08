#include "actor/Actor.h"

class BaseActor : public Actor {
  protected:
    friend class Game;

    BaseActor();
    void HandleInput(const bool keys[]) override;
    void HandleUpdate(float deltaTime) override;

  private:
};