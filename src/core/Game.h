#pragma once
#include "SDL3/SDL.h"
#include "actor/Actor.h"
#include "component/RenderComponent.h"
#include <string>
#include <unordered_map>
#include <vector>

class Game {
  public:
    bool Initialize();
    bool RunIteration(); // 游戏每帧循环
    void Shutdown();
    // 接收来自 SDL 的事件
    void HandleEvent(const SDL_Event *event);
    // 新建游戏对象
    template <typename T> T *CreateActor() {
        T *actor = new T();
        mActors.emplace_back(actor);
        return actor;
    }
    // 获取贴图资源
    SDL_Texture *GetTexture(std::string file);
    // 为 RenderComponent 提供注册
    void AddRender(RenderComponent *);
    void RemoveRender(RenderComponent *);

  private:
    // 工具类
    SDL_Window *sdlWindow = nullptr;     // 游戏界面类
    SDL_Renderer *sdlRenderer = nullptr; // 渲染器类
    // 游戏资源
    std::vector<Actor *> mActors;                             // 游戏对象
    std::unordered_map<std::string, SDL_Texture *> mTextures; // 游戏图像资源
    std::vector<class RenderComponent *> mRenders;            // 游戏需要渲染的组件
    // 游戏参数
    bool running = true;       // 游戏当前是否在运行
    const bool *keyboardState; // 当前帧键盘事件状态
    Uint64 prevTime = 0;       // 上一帧的时间
    double deltaTime = 0.0f;   // 上一帧到这一帧经过的时间

    bool ProcessInput();   // 当前帧处理输入
    bool UpdateGame();     // 当前帧更新游戏内部状态
    bool GenerateOutput(); // 当前帧进行输出
    void LoadData();       // 游戏开始时加载数据
    void UnloadData();     // 游戏结束时释放资源
};

// 全局游戏框架对象
extern Game gGame;