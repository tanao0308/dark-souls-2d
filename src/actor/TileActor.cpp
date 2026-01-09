#include "actor/TileActor.h"

// public

// protected
TileActor::TileActor(Vector2 tilePos, int layer, TileType tileType) : tileType(tileType) {
    // 设置当前区块的位置属性
    m_transform.SetTileCenterPosition(tilePos);
    m_transform.SetLayer(layer);
}
TileActor::~TileActor() {}
void TileActor::HandleInput(const bool keys[]) {}
void TileActor::HandleUpdate(float deltaTime) {}

// private