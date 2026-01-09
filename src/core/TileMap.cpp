// #include "TileMap.h"
// #include "core/Game.h"

// TileMap::TileMap(int width, int height, int layers) : width_(width), height_(height), layers_(layers) {
//     tiles_.resize(layers_);
//     for (int l = 0; l < layers_; ++l) {
//         tiles_[l].resize(height_);
//         for (int y = 0; y < height_; ++y) {
//             tiles_[l][y].resize(width_, nullptr);
//         }
//     }
// }

// void TileMap::GenerateTiles() {
//     for (int l = 0; l < layers_; ++l) {
//         for (int y = 0; y < height_; ++y) {
//             for (int x = 0; x < width_; ++x) {
//                 tiles_[l][y][x] = new TileActor(TilePos(x, y, l));
//             }
//         }
//     }
// }

// TileActor *TileMap::GetTileAt(int x, int y, int layer) const {
//     if (layer < 0 || layer >= layers_ || y < 0 || y >= height_ || x < 0 || x >= width_)
//         return nullptr;
//     return tiles_[layer][y][x];
// }

// bool TileMap::IsWalkable(int x, int y, int layer) const {
//     TileActor *tile = GetTileAt(x, y, layer);
//     if (!tile)
//         return false;
//     // 这里可以访问 tile 的属性，比如 tile->IsSolid()
//     return tile->isWalkable;
// }

// void TileMap::AddToGame(Game *game) {
//     for (int l = 0; l < layers_; ++l) {
//         for (int y = 0; y < height_; ++y) {
//             for (int x = 0; x < width_; ++x) {
//                 game->AddActor(tiles_[l][y][x]);
//             }
//         }
//     }
// }
