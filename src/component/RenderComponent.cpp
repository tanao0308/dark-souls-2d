#include "component/RenderComponent.h"
#include "actor/Actor.h"
#include "actor/CameraActor.h"
#include "core/Game.h"
#include "spdlog/spdlog.h"
#include "utils/Math.h"

// public
void RenderComponent::SetDrawOrder(RenderOrder order) { m_drawOrder = order; }
RenderOrder RenderComponent::GetDrawOrder() const { return m_drawOrder; }
void RenderComponent::SetTexture(SDL_Texture *texture) { m_texture = texture; }
void RenderComponent::Draw(SDL_Renderer *renderer, const Transform &camera) const {
    if (!m_texture) {
        return;
    }
    // 获取相机变换后的位置矩阵
    const auto tran = GetOwner()->GetTransform().ToCameraTransform(camera);
    // 获取位置矩阵、角度
    auto rect = tran.GetRealRect();                     // 可能需要进一步处理结果
    auto degree = -Math::ToDegrees(tran.GetRotation()); // 可能需要进一步处理结果
    // 进行绘制
    if (!SDL_RenderTextureRotated(renderer, m_texture, nullptr, &rect, degree, nullptr, SDL_FLIP_NONE)) {
        spdlog::error("RenderComponent::Draw() failed, {}", SDL_GetError());
    }
    spdlog::debug("RenderComponent::Draw() {}", tran.ToString());
    return;
}
// protected:
RenderComponent::RenderComponent(class Actor *owner) : Component(owner) { gGame.AddRender(this); }
RenderComponent::~RenderComponent() { gGame.RemoveRender(this); }
void RenderComponent::HandleInput(const bool keys[]) { spdlog::debug("RenderComponent::HandleInput()"); }
void RenderComponent::HandleUpdate(float deltaTime) { spdlog::debug("RenderComponent::HandleUpdate()"); }
// private