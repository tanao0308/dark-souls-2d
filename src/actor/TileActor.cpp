#include "actor/TileActor.h"

// public
TilePos TileActor::GetTilePos() { return tilePos; }
TilePos TileActor::~GetTilePos() {}

// protected
TileActor::TileActor(TilePos tilePos, TileType tileType) : tilePos(tilePos), tileType(tileType) {}
void TileActor::HandleInput(const bool keys[]) {}
void TileActor::HandleUpdate(float deltaTime) {}

// private