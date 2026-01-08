//
// Created by Sanjay on 7/19/2025.
//

#include "component/RenderComponent.h"
#include "actor/Actor.h"
#include "core/Game.h"
#include "utils/Math.h"

void RenderComponent::SetTexture(SDL_Texture *texture) { texture = texture; }
void RenderComponent::Draw(SDL_Renderer *renderer) {
    if (!texture) {
        return;
    }
    // 获取纹理绘制的目标位置 Transform
    SDL_FRect rect;
    if (!SDL_GetTextureSize(texture, &rect.w, &rect.h)) {
        SDL_Log("Draw() failed, %s", SDL_GetError());
    }
    auto &transform = GetOwner()->GetTransform();
    rect.w *= transform.GetScale();
    rect.h *= transform.GetScale();
    rect.x = transform.GetPosition().x - rect.w / 2;
    rect.y = transform.GetPosition().y - rect.h / 2;
    // 进行绘制
    if (!SDL_RenderTextureRotated(renderer, texture, nullptr, &rect, -Math::ToDegrees(transform.GetRotation()), nullptr,
                                  SDL_FLIP_NONE)) {
        SDL_Log("Draw() failed, %s", SDL_GetError());
    }
    return;
}
void RenderComponent::SetDrawOrder(const int order) { drawOrder = order; }
int RenderComponent::GetDrawOrder() const { return drawOrder; }
// protected:
RenderComponent::RenderComponent(class Actor *owner) : Component(owner) { gGame.AddRender(this); }
RenderComponent::~RenderComponent() { gGame.RemoveRender(this); }
void RenderComponent::HandleInput(const bool keys[]) {}
void RenderComponent::HandleUpdate(float deltaTime) {}
// private