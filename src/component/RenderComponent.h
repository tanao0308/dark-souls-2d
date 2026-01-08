#pragma once

#include "SDL3/SDL.h"
#include "utils/Enums.h"
#include "component/Component.h"
#include "utils/Transform.h"

class RenderComponent : public Component {
  public:
    // 设置绘图顺序
    void SetDrawOrder(RenderOrder order);
    RenderOrder GetDrawOrder() const;
    virtual void SetTexture(SDL_Texture *texture); // 设置贴图
    virtual void Draw(SDL_Renderer *renderer, const Transform &camera) const;     // 绘制贴图

  protected:
    friend class Actor;
    SDL_Texture *texture;
    RenderOrder drawOrder = RenderOrder::NONE;

    RenderComponent(class Actor *owner); // 防止在 Actor 外被创建
    ~RenderComponent();
    void HandleInput(const bool keys[]) override;
    void HandleUpdate(float deltaTime) override;

  private:
};