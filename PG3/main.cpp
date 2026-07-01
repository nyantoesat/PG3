#include <stdio.h>
#include <cstdlib>
#include <Windows.h>
#include <cmath>


class PowerUpItem {
private:
    int attackBonus;
    char type[32];
public:
    PowerUpItem(int bonus, const char* t) {
        attackBonus = bonus;
        for (int i = 0; i < 32; i++) type[i] = t[i];
    }
    int getBonus() { return attackBonus; }
    void applyEffect() {
        printf("パワーアップ! 攻撃力 +%d\n", attackBonus);
    }
    void spawn() {
        printf("アイテム '%s' が出現した!\n", type);
    }
};

// ===== Bullet =====
class Bullet {
private:
    float speed;
    int damage;
public:
    Bullet(float s, int d) {
        speed = s;
        damage = d;
    }
    void move() {
        printf("弾が速度 %.1f で移動中...\n", speed);
    }
    void hitCheck() {
        printf("弾がヒット! ダメージ: %d\n", damage);
    }
};


class Player {
private:
    int life;
    int attackPower;
    float speed;
public:
    Player(int l, int atk, float spd) {
        life = l;
        attackPower = atk;
        speed = spd;
    }
    int getLife() { return life; }
    int getAttackPower() { return attackPower; }

    void move() {
        printf("プレイヤーが速度 %.1f で移動中\n", speed);
    }
    Bullet* shoot() {
        printf("プレイヤーが弾を発射! 攻撃力: %d\n", attackPower);
        return new Bullet(10.0f, attackPower);
    }
    void collectItem(PowerUpItem* item) {
        attackPower += item->getBonus();
        item->applyEffect();
        printf("現在の攻撃力: %d\n", attackPower);
    }
    void takeDamage(int dmg) {
        life -= dmg;
        printf("プレイヤーがダメージを受けた! 残りライフ: %d\n", life);
        if (life <= 0) {
            printf("ゲームオーバー!\n");
        }
    }
};


class Enemy {
protected:
    int health;
    int attackPower;
public:
    Enemy(int hp, int atk) {
        health = hp;
        attackPower = atk;
    }
    virtual void move() = 0;
    virtual void attack(Player* player) = 0;
    virtual ~Enemy() {}

    void takeDamage(int dmg) {
        health -= dmg;
        printf("敵がダメージを受けた! 残りHP: %d\n", health);
    }
    bool isDefeated() { return health <= 0; }
};


class StraightEnemy : public Enemy {
private:
    float direction;
public:
    StraightEnemy(int hp, int atk, float dir)
        : Enemy(hp, atk) {
        direction = dir;
    }
    void move() override {
        printf("直進敵: 方向 %.1f で直進移動\n", direction);
    }
    void attack(Player* player) override {
        printf("直進敵の攻撃! ダメージ: %d\n", attackPower);
        player->takeDamage(attackPower);
    }
};


class ChaseEnemy : public Enemy {
private:
    Player* target;
public:
    ChaseEnemy(int hp, int atk, Player* p)
        : Enemy(hp, atk) {
        target = p;
    }
    void move() override {
        printf("追尾敵: プレイヤーを追跡中\n");
    }
    void attack(Player* player) override {
        printf("追尾敵の攻撃! ダメージ: %d\n", attackPower);
        player->takeDamage(attackPower);
    }
};


class ZigzagEnemy : public Enemy {
private:
    float amplitude;
public:
    ZigzagEnemy(int hp, int atk, float amp)
        : Enemy(hp, atk) {
        amplitude = amp;
    }
    void move() override {
        printf("ジグザグ敵: 振幅 %.1f でジグザグ移動\n", amplitude);
    }
    void attack(Player* player) override {
        printf("ジグザグ敵の攻撃! ダメージ: %d\n", attackPower);
        player->takeDamage(attackPower);
    }
};


class Stage {
private:
    int stageNumber;
    Enemy* enemies[3];
    int enemyCount;
public:
    Stage(int num) {
        stageNumber = num;
        enemyCount = 0;
    }
    void addEnemy(Enemy* e) {
        if (enemyCount < 3) {
            enemies[enemyCount++] = e;
        }
    }
    void start() {
        printf("\n===== ステージ %d 開始! =====\n", stageNumber);
    }
    void spawnEnemy() {
        printf("敵が %d 体出現!\n", enemyCount);
        for (int i = 0; i < enemyCount; i++) {
            enemies[i]->move();
        }
    }
    bool isCleared() {
        for (int i = 0; i < enemyCount; i++) {
            if (!enemies[i]->isDefeated()) return false;
        }
        return true;
    }
    Enemy** getEnemies() { return enemies; }
    int getEnemyCount() { return enemyCount; }
};

int main() {
    system("chcp 65001 > nul");

    Player* player = new Player(10, 3, 5.0f);
    int totalStages = 3;

    for (int stageNum = 1; stageNum <= totalStages; stageNum++) {

        // ライフが0以下ならゲームオーバー
        if (player->getLife() <= 0) break;

        Stage* stage = new Stage(stageNum);

        // ステージごとに敵の強さを変える
        if (stageNum == 1) {
            stage->addEnemy(new StraightEnemy(5, 1, 90.0f));
            stage->addEnemy(new ChaseEnemy(8, 2, player));
        }
        else if (stageNum == 2) {
            stage->addEnemy(new StraightEnemy(10, 2, 90.0f));
            stage->addEnemy(new ChaseEnemy(12, 3, player));
            stage->addEnemy(new ZigzagEnemy(8, 2, 3.0f));
        }
        else if (stageNum == 3) {
            stage->addEnemy(new StraightEnemy(15, 3, 90.0f));
            stage->addEnemy(new ChaseEnemy(18, 4, player));
            stage->addEnemy(new ZigzagEnemy(12, 3, 4.0f));
        }

        stage->start();
        stage->spawnEnemy();

        printf("\n--- 戦闘開始 ---\n");

       
        Enemy** enemies = stage->getEnemies();
        for (int i = 0; i < stage->getEnemyCount(); i++) {

        
            if (player->getLife() <= 0) break;

            printf("\n-- 敵 %d と戦闘中 --\n", i + 1);

            
            while (!enemies[i]->isDefeated()) {
                if (player->getLife() <= 0) break;

            
                Bullet* bullet = player->shoot();
                bullet->hitCheck();
                enemies[i]->takeDamage(player->getAttackPower());
                delete bullet;

         
                if (!enemies[i]->isDefeated()) {
                    enemies[i]->attack(player);
                }
            }

        
            if (enemies[i]->isDefeated()) {
                printf("敵 %d を倒した!\n", i + 1);
                PowerUpItem* item = new PowerUpItem(1, "AttackUp");
                item->spawn();
                player->collectItem(item);
                delete item;
            }
        }

     
        if (stage->isCleared()) {
            printf("\n===== ステージ %d クリア! =====\n", stageNum);
        }

        for (int i = 0; i < stage->getEnemyCount(); i++) {
            delete enemies[i];
        }
        delete stage;
    }


    if (player->getLife() > 0) {
        printf("\n===== ゲームクリア! おめでとう! =====\n");
    }
    else {
        printf("\n===== ゲームオーバー =====\n");
    }

    delete player;
    return 0;
}