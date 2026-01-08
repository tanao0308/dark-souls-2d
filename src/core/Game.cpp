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
    sdlWindow = SDL_CreateWindow("MyWindow", WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!sdlWindow) {
        SDL_Log("初始化 窗口 失败");
        return false;
    }
    // 初始化渲染器
    sdlRenderer = SDL_CreateRenderer(sdlWindow, nullptr);
    if (!sdlRenderer) {
        SDL_Log("初始化 渲染器 失败");
        return false;
    }

    Random::Init();

    // 加载数据
    LoadData();
    prevTime = SDL_GetTicks();
    return true;
}
bool Game::RunIteration() {
    running &= ProcessInput();
    running &= UpdateGame();
    running &= GenerateOutput();
    return running;
}
void Game::Shutdown() {
    // 清除数据
    UnloadData();
    // SDL 善后
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);
    SDL_Quit();
    return;
}
void Game::HandleEvent(const SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT) {
        running = false;
    }
    return;
}
SDL_Texture *Game::GetTexture(std::string file) {
    if (mTextures.count(file)) {
        return mTextures[file];
    }
    auto surface = IMG_Load(file.c_str());
    if (!surface) {
        SDL_Log("GetTexture() 获取surface失败");
        return nullptr;
    }
    auto texture = SDL_CreateTextureFromSurface(sdlRenderer, surface);
    SDL_DestroySurface(surface);
    mTextures[file] = texture;
    return texture;
}
void Game::AddRender(RenderComponent *sc) { mRenders.push_back(sc); }
void Game::RemoveRender(RenderComponent *sc) { std::erase(mRenders, sc); }

// private
bool Game::ProcessInput() {
    keyboardState = SDL_GetKeyboardState(nullptr);
    if (keyboardState[SDL_SCANCODE_ESCAPE]) {
        running = false;
    }
    for (auto actor : mActors) {
        actor->Input(keyboardState);
    }
    return true;
}
bool Game::UpdateGame() {
    Uint64 curTime = SDL_GetTicks();
    deltaTime = Math::Min(0.033f, (curTime - prevTime) / 1000.0f);
    prevTime = curTime;

    for (auto actor : mActors) {
        actor->Update(deltaTime);
    }

    return true;
}
bool Game::GenerateOutput() {
    /*
    // 设置渲染器颜色
    if (!SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255)) {
        SDL_Log("设置渲染器颜色失败");
        return false;
    }
    // 使用颜色刷新界面
    if (!SDL_RenderClear(sdlRenderer)) {
        SDL_Log("刷新背景界面失败");
        return false;
    }
    // 设置渲染器颜色
    if (!SDL_SetRenderDrawColor(sdlRenderer, 0, 255, 255, 255)) {
        SDL_Log("设置渲染器颜色失败");
        return false;
    }
    */
    // 优先级排序 Actor
    std::ranges::stable_sort(mRenders, [](const RenderComponent *a, const RenderComponent *b) {
        return a->GetDrawOrder() < b->GetDrawOrder();
    });
    // 渲染 Actor
    for (auto sc : mRenders) {
        sc->Draw(sdlRenderer);
    }
    if (!SDL_RenderPresent(sdlRenderer)) {
        SDL_Log("推送渲染失败");
        return false;
    }
    return true;
}
void Game::LoadData() {
    // 创建地图actor（临时）
    Actor *bgActor = CreateActor<BaseActor>();
    mActors.push_back(bgActor);
    bgActor->GetTransform().SetPosition({WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2});
    RenderComponent *bgRender = bgActor->CreateComponent<RenderComponent>();
    bgRender->SetTexture(GetTexture("Assets/Stars.png"));
    bgRender->SetDrawOrder(-42);

    // 创建玩家actor
    Actor *playerActor = CreateActor<PlayerActor>();

    // 创建镜头actor
    CreateActor<CameraActor>();
}
void Game::UnloadData() {
    // 释放游戏对象
    for (auto actor : mActors) {
        delete actor;
    }
    // 释放图片资源
    for (auto it : mTextures) {
        SDL_DestroyTexture(it.second);
    }
}

Game gGame;