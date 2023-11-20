#include <iostream>

class Entity {
  public:
    virtual void getEntity() {}
};

class Player : public Entity {

};

class Enemy : public Entity {

};

int main(){
  Player* player  = new Player();
  Entity* e = player;
  // 编译器不知道e是指向player的，需要dynamic_cast<>
  Player* p = dynamic_cast<Player*>(e);
}