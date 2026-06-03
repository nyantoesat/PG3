#include <iostream>
#include <cstddef>

class Enemy {
public:
    Enemy() {}
    void Update();

private:
    void Approach();
    void Attack();
    void Retreat();

    enum class Phase { Approach, Attack, Retreat };

    Phase phase_ = Phase::Approach;
    int timer_ = 0;

    static void (Enemy::* spFuncTable[])();
};


void (Enemy::* Enemy::spFuncTable[])() = {
    &Enemy::Approach,
    &Enemy::Attack,
    &Enemy::Retreat,
};

void Enemy::Update() {
    (this->*spFuncTable[static_cast<size_t>(phase_)])();
    timer_++;
    const char* names[] = { "Approach", "Attack", "Retreat" };
    std::cout << "Phase: " << names[static_cast<size_t>(phase_)]
        << "  timer: " << timer_ << "\n";
}

void Enemy::Approach() {
    if (timer_ >= 60) { phase_ = Phase::Attack; timer_ = 0; }
}

void Enemy::Attack() {
    if (timer_ >= 60) { phase_ = Phase::Retreat; timer_ = 0; }
}

void Enemy::Retreat() {
   
}

int main() {
    Enemy enemy;
    for (int i = 0; i < 200; i++) {
        enemy.Update();
    }
}