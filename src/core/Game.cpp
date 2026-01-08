#include "core/Game.h"
#include "SDL3_image/SDL_image.h"
#include "actor/BaseActor.h"
#include "actor/CameraActor.h"
#include "actor/CamreaActor.h"
#include "actor/PlayerActor.h"
#include "utils/Enums.h"
#include "utils/Random.h"
#include <algorithm>

// public
bool Game::Initialize() {
    // 设置 60 帧运行
    SDL_SetHint("SDL_MAIN_CALLBACK_RATE", "60");
    // 初始化 SDL，需要 audio 和 video
    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO)) {
        SDL_Log("初始化 SDL 失败");
        return false;
    }
    // 初始化窗口
    m_sdlWindow = SDL_CreateWindow("MyWindow", WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!m_sdlWindow) {
        SDL_Log("初始化 窗口 失败");
        return false;
    }
    // 初始化渲染器
    m_sdlRenderer = SDL_CreateRenderer(m_sdlWindow, nullptr);
    if (!m_sdlRenderer) {
        SDL_Log("初始化 渲染器 失败");
        return false;
    }

    Random::Init();

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
    if (m_Textures.count(file)) {
        return m_Textures[file];
    }
    auto surface = IMG_Load(file.c_str());
    if (!surface) {
        SDL_Log("GetTexture() 获取surface失败");
        return nullptr;
    }
    auto texture = SDL_CreateTextureFromSurface(m_sdlRenderer, surface);
    SDL_DestroySurface(surface);
    m_Textures[file] = texture;
    return texture;
}
void Game::AddRender(RenderComponent *sc) { m_Renders.push_back(sc); }
void Game::RemoveRender(RenderComponent *sc) { std::erase(m_Renders, sc); }

// private
bool Game::ProcessInput() {
    m_keyboardState = SDL_GetKeyboardState(nullptr);
    if (m_keyboardState[SDL_SCANCODE_ESCAPE]) {
        m_running = false;
    }
    for (auto actor : m_Actors) {
        actor->Input(m_keyboardState);
    }
    return true;
}
bool Game::UpdateGame() {
    Uint64 curTime = SDL_GetTicks();
    m_deltaTime = Math::Min(0.033f, (curTime - m_prevTime) / 1000.0f);
    m_prevTime = curTime;

    for (auto actor : m_Actors) {
        actor->Update(m_deltaTime);
    }

    return true;
}
bool Game::GenerateOutput() {
    // 优先级排序 Actor
    std::ranges::stable_sort(m_Renders, [](const RenderComponent *a, const RenderComponent *b) {
        return a->GetDrawOrder() < b->GetDrawOrder();
    });
    // 渲染 Actor
    for (auto sc : m_Renders) {
        sc->Draw(m_sdlRenderer);
    }
    if (!SDL_RenderPresent(m_sdlRenderer)) {
        SDL_Log("推送渲染失败");
        return false;
    }
    return true;
}
void Game::LoadData() {
    // 创建地图actor（临时）
    Actor *bgActor = CreateActor<BaseActor>();
    m_Actors.push_back(bgActor);
    bgActor->GetTransform().SetPosition({WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2});
    RenderComponent *bgRender = bgActor->CreateComponent<RenderComponent>();
    bgRender->SetTexture(GetTexture("Assets/Stars.png"));
    bgRender->SetDrawOrder(RenderOrder::MAP);

    // 创建玩家actor
    Actor *playerActor = CreateActor<PlayerActor>();

    // 创建镜头actor
    CreateActor<CameraActor>(playerActor);
}
void Game::UnloadData() {
    // 释放游戏对象
    for (auto actor : m_Actors) {
        delete actor;
    }
    // 释放图片资源
    for (auto it : m_Textures) {
        SDL_DestroyTexture(it.second);
    }
}

Game gGame;