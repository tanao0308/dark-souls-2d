#pragma once
#include "component/Component.h"
#include "utils/Transform.h"
#include <vector>

// 游戏角色对象基类
class Actor {
  public:
    // 获取位置
    Transform &GetTransform();
    const Transform &GetTransform() const;

    template <typename T> T *CreateComponent() {
        T *component = new T(this);
        mComponents.emplace_back(component);
        return component;
    }

    void Input(const bool keys[]);
    void Update(float deltaTime);

  protected:
    friend class Game; // 友元声明在任何位置，权限都是能访问 private

    Transform transform; // 物理状态信息

    Actor();              // 为了仅能从 Game 类创建游戏对象，设置为 protected
    virtual ~Actor() = 0; // 同理，只能在 Game 内部销毁
    virtual void HandleInput(const bool keys[]) = 0;
    virtual void HandleUpdate(float deltaTime) = 0;

  private:
    std::vector<Component *> mComponents; // 自身持有的组件（多态）
};
