//
// Created by Sanjay on 7/19/2025.
//
#pragma once

#include "SDL3/SDL.h"
#include "component/Component.h"

class RenderComponent : public Component {
  public:
    virtual void SetTexture(SDL_Texture *texture);
    virtual void Draw(SDL_Renderer *renderer);
    void SetDrawOrder(const int order);
    int GetDrawOrder() const;

  protected:
    friend class Actor;
    SDL_Texture *texture;
    int drawOrder = 0;

    RenderComponent(class Actor *owner); // 防止在 Actor 外被创建
    ~RenderComponent();
    void HandleInput(const bool keys[]) override;
    void HandleUpdate(float deltaTime) override;

  private:
};