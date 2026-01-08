#include "actor/PlayerActor.h"
#include "core/Game.h"
#include "utils/Enums.h"
#include "utils/Random.h"

// public

// protected
PlayerActor::PlayerActor() {
    // 初始化位置
    GetTransform().SetScale(kScale);
    GetTransform().SetRotation(kRotation);

    // 初始化渲染组件
    m_render = CreateComponent<RenderComponent>();
    m_render->SetTexture(gGame.GetTexture("Assets/Player.png"));
    m_render->SetDrawOrder(RenderOrder::PLAYER);

    // 初始化移动组件
    m_move = CreateComponent<MoveComponent>();
}
PlayerActor::~PlayerActor() {}
void PlayerActor::HandleInput(const bool keys[]) {
    m_move->SetPosSpeed(posSpeed);

    Vector2 tarDir = tarActor->GetTransform().GetPosition() - GetTransform().GetPosition();
    float tarRot = atan2(-tarDir.y, tarDir.x);
    float curRot = GetTransform().GetRotation();
    float deltaRot = tarRot - curRot;
    while (deltaRot > Math::Pi) {
        deltaRot -= Math::TwoPi;
    }
    while (deltaRot < -Math::Pi) {
        deltaRot += Math::TwoPi;
    }
    if (deltaRot < 0) {
        m_move->SetRotSpeed(-rotSpeed);
    } else {
        m_move->SetRotSpeed(+rotSpeed);
    }
}
void PlayerActor::HandleUpdate(float deltaTime) {}

// private