#include "core/Game.h"
#include "SDL3_image/SDL_image.h"
#include "actor/BaseActor.h"
#include "actor/CameraActor.h"
#include "actor/PlayerActor.h"
#include "spdlog/spdlog.h"
#include "utils/Enums.h"
#include "utils/Random.h"
#include <algorithm>

// public
bool Game::Initialize() {
    // 设置 60 帧运行
    SDL_SetHint("SDL_MAIN_CALLBACK_RATE", "60");
    // 初始化 SDL，需要 audio 和 video
    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO)) {
        spdlog::info("初始化 SDL 失败");
        return false;
    }
    // 初始化窗口
    m_sdlWindow = SDL_CreateWindow("MyWindow", WINDOW_WIDTH * TILE_SIZE, WINDOW_HEIGHT * TILE_SIZE, 0);
    if (!m_sdlWindow) {
        spdlog::info("初始化 窗口 失败");
        return false;
    }
    // 初始化渲染器
    m_sdlRenderer = SDL_CreateRenderer(m_sdlWindow, nullptr);
    if (!m_sdlRenderer) {
        spdlog::info("初始化 渲染器 失败");
        return false;
    }

    Random::Init();
    spdlog::set_level(spdlog::level::debug);

    // 加载数据
    LoadData();
    m_prevTime = SDL_GetTicks();
    return true;
}
bool Game::RunIteration() {
    m_running &= ProcessInput();
    m_running &= UpdateGame();
    m_running &= GenerateOutput();
    return m_running;
}
void Game::Shutdown() {
    // 清除数据
    UnloadData();
    // SDL 善后
    SDL_DestroyRenderer(m_sdlRenderer);
    SDL_DestroyWindow(m_sdlWindow);
    SDL_Quit();
    return;
}
void Game::HandleEvent(const SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT) {
        m_running = false;
    }
    return;
}
SDL_Texture *Game::GetTexture(std::string file) {
    if (m_textures.count(file)) {
        return m_textures[file];
    }
    auto surface = IMG_Load(file.c_str());
    if (!surface) {
        spdlog::info("GetTexture() 获取surface失败");
        return nullptr;
    }
    auto texture = SDL_CreateTextureFromSurface(m_sdlRenderer, surface);
    SDL_DestroySurface(surface);
    m_textures[file] = texture;
    return texture;
}
void Game::AddRender(RenderComponent *sc) { m_renders.push_back(sc); }
void Game::RemoveRender(RenderComponent *sc) { std::erase(m_renders, sc); }

// private
bool Game::ProcessInput() {
    spdlog::debug("Game::ProcessInput()");
    m_keyboardState = SDL_GetKeyboardState(nullptr);
    if (m_keyboardState[SDL_SCANCODE_ESCAPE]) {
        m_running = false;
    }
    for (auto actor : m_actors) {
        actor->Input(m_keyboardState);
    }
    return true;
}
bool Game::UpdateGame() {
    spdlog::debug("Game::UpdateGame()");
    // 更新当前帧时间
    Uint64 curTime = SDL_GetTicks();
    m_deltaTime = Math::Min(0.033f, (curTime - m_prevTime) / 1000.0f);
    m_prevTime = curTime;

    for (auto actor : m_actors) {
        actor->Update(m_deltaTime);
    }

    return true;
}
bool Game::GenerateOutput() {
    spdlog::debug("Game::GenerateOutput()");
    // 设置渲染器颜色
    if (!SDL_SetRenderDrawColor(m_sdlRenderer, 0, 0, 0, 255)) {
        SDL_Log("设置渲染器颜色失败");
        return false;
    }
    // 使用颜色刷新界面
    if (!SDL_RenderClear(m_sdlRenderer)) {
        SDL_Log("刷新背景界面失败");
        return false;
    }
    // 设置渲染器颜色
    if (!SDL_SetRenderDrawColor(m_sdlRenderer, 0, 255, 255, 255)) {
        SDL_Log("设置渲染器颜色失败");
        return false;
    }

    // 优先级排序 Actor
    std::ranges::stable_sort(m_renders, [](const RenderComponent *a, const RenderComponent *b) {
        return a->GetDrawOrder() < b->GetDrawOrder();
    });
    // 渲染 Actor
    for (auto sc : m_renders) {
        sc->Draw(m_sdlRenderer, m_camera->GetTransform());
    }
    if (!SDL_RenderPresent(m_sdlRenderer)) {
        spdlog::info("推送渲染失败");
        return false;
    }
    return true;
}
void Game::LoadData() {
    // 创建地图actor（临时）
    spdlog::info("LoadData 加载地图中。。。");
    Actor *mapActor = CreateActor<BaseActor>();
    mapActor->GetTransform().SetTileCenterPosition({WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2});
    mapActor->GetTransform().SetTileSize({WINDOW_WIDTH, WINDOW_HEIGHT});
    mapActor->GetTransform().SetRotation(Math::Pi / 2);
    RenderComponent *mapRender = mapActor->CreateComponent<RenderComponent>();
    mapRender->SetTexture(GetTexture("Assets/Stars.png"));
    mapRender->SetDrawOrder(RenderOrder::MAP);

    // 创建玩家actor
    spdlog::info("LoadData 加载玩家中。。。");
    m_player = CreateActor<PlayerActor>();
    if (!m_player)
        spdlog::debug("m_player is {}");

    // 创建镜头actor
    spdlog::info("LoadData 加载镜头中。。。");
    m_camera = CreateActor<CameraActor>(m_player);
}
void Game::UnloadData() {
    // 释放游戏对象
    for (auto actor : m_actors) {
        delete actor;
    }
    // 释放图片资源
    for (auto it : m_textures) {
        SDL_DestroyTexture(it.second);
    }
}

Game gGame;