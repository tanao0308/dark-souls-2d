#include "component/RenderComponent.h"
#include "actor/Actor.h"
#include "actor/CameraActor.h"
#include "core/Game.h"
#include "utils/Math.h"

// public
void RenderComponent::SetDrawOrder(RenderOrder order) { drawOrder = order; }
RenderOrder RenderComponent::GetDrawOrder() const { return drawOrder; }
void RenderComponent::SetTexture(SDL_Texture *texture) { texture = texture; }
void RenderComponent::Draw(SDL_Renderer *renderer, const Transform &camera) const {
    if (!texture) {
        return;
    }
    // 获取相机变换后的位置矩阵
    const auto tran = GetOwner()->GetTransform().GetCameraTransform(camera);
    // 获取位置矩阵、角度
    auto rect = tran.GetRect();                         // 可能需要进一步处理结果
    auto degree = -Math::ToDegrees(tran.GetRotation()); // 可能需要进一步处理结果
    // 进行绘制
    if (!SDL_RenderTextureRotated(renderer, texture, nullptr, &rect, degree, nullptr, SDL_FLIP_NONE)) {
        SDL_Log("Draw() failed, %s", SDL_GetError());
    }
    return;
}
// protected:
RenderComponent::RenderComponent(class Actor *owner) : Component(owner) { gGame.AddRender(this); }
RenderComponent::~RenderComponent() { gGame.RemoveRender(this); }
void RenderComponent::HandleInput(const bool keys[]) {}
void RenderComponent::HandleUpdate(float deltaTime) {}
// private