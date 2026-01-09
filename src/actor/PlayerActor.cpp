#include "actor/PlayerActor.h"
#include "core/Game.h"
#include "utils/Enums.h"
#include "utils/Random.h"

// public

// protected
PlayerActor::PlayerActor() : kSize(20.0f, 20.0f) {
    // 初始化位置
    m_transform.SetTileCenterPosition({WINDOW_WIDTH/2, WINDOW_HEIGHT/2});
    m_transform.SetTileSize(kSize);
    m_transform.SetRotation(kRotation);

    // 初始化渲染组件
    m_render = CreateComponent<RenderComponent>();
    m_render->SetTexture(gGame.GetTexture("Assets/Ship.png"));
    m_render->SetDrawOrder(RenderOrder::PLAYER);

    // 初始化移动组件
    m_move = CreateComponent<MoveComponent>();
}
PlayerActor::~PlayerActor() {}
void PlayerActor::HandleInput(const bool keys[]) {
    int posMove = keys[SDL_SCANCODE_W] - keys[SDL_SCANCODE_S];
    int rotMove = keys[SDL_SCANCODE_A] - keys[SDL_SCANCODE_D];
    this->m_move->SetPosSpeed(posMove * kPosSpeed);
    this->m_move->SetRotSpeed(rotMove * kRotSpeed);
}
void PlayerActor::HandleUpdate(float deltaTime) {}

// private