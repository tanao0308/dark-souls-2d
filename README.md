# 项目结构
## Game.h/Game.cpp
    游戏主循环框架
    mainloop: 
        ProcessInput()
        UpdateGame()
        GenerateOutput()
## Actor.h/Actor.cpp
    游戏对象类
    Input(), HandleInput() 对应mainloop，表示基类函数和派生函数
    Update(), HandleUpdate() 同上
## Component.h/Component.cpp
    游戏组件类，和Actor无继承关系，但是属于某个Actor
### RenderComponent
    渲染组件，实现贴图功能
### MoveComponent
    动作组件，实现移动功能