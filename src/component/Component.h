#pragma once

class Actor;

/*
游戏角色的组件
*/
class Component {
  public:
    Actor *GetOwner() const;
    void Input(const bool keys[]);
    void Update(float deltaTime);

  protected:
    friend class Actor;
    Actor *actor;

    Component(Actor *actor);
    virtual ~Component();
    virtual void HandleInput(const bool keys[]) = 0;
    virtual void HandleUpdate(float deltaTime) = 0;

  private:
};