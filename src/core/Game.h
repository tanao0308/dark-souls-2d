#pragma once
#include "SDL3/SDL.h"
#include "actor/Actor.h"
#include "actor/CameraActor.h"
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
    template <typename T, typename... Args> T *CreateActor(Args &&...args) {
        T *actor = new T(std::forward<Args>(args)...);
        m_actors.emplace_back(actor);
        return actor;
    }
    // 获取贴图资源
    SDL_Texture *GetTexture(std::string file);
    // 为 RenderComponent 提供注册
    void AddRender(RenderComponent *);
    void RemoveRender(RenderComponent *);

  private:
    // 工具类
    SDL_Window *m_sdlWindow = nullptr;     // 游戏界面类
    SDL_Renderer *m_sdlRenderer = nullptr; // 渲染器类
    // 游戏资源
    std::vector<Actor *> m_actors;                             // 游戏对象
    std::unordered_map<std::string, SDL_Texture *> m_textures; // 游戏图像资源
    std::vector<class RenderComponent *> m_renders;            // 游戏需要渲染的组件
    // 游戏参数
    bool m_running = true;       // 游戏当前是否在运行
    const bool *m_keyboardState; // 当前帧键盘事件状态
    Uint64 m_prevTime = 0;       // 上一帧的时间
    double m_deltaTime = 0.0f;   // 上一帧到这一帧经过的时间
    // 特殊游戏对象
    PlayerActor *m_player = nullptr;
    CameraActor *m_camera = nullptr;

    bool ProcessInput();   // 当前帧处理输入
    bool UpdateGame();     // 当前帧更新游戏内部状态
    bool GenerateOutput(); // 当前帧进行输出
    void LoadData();       // 游戏开始时加载数据
    void UnloadData();     // 游戏结束时释放资源
};

// 全局游戏框架对象
extern Game gGame;