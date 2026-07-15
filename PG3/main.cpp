#include <stdio.h>
#include <cstdlib>
#include <Windows.h>

// ===== 基底クラス：Animal =====
class Animal {
protected:
    const char* name;
public:
    Animal(const char* n) {
        name = n;
    }
    virtual void speak() = 0;  // 純粋仮想関数
    virtual ~Animal() {}
};

// ===== Dog クラス =====
class Dog : public Animal {
public:
    Dog(const char* n) : Animal(n) {}

    void speak() override {
        printf("%sは言います：ワン!\n", name);
    }
};

// ===== Cat クラス =====
class Cat : public Animal {
public:
    Cat(const char* n) : Animal(n) {}

    void speak() override {
        printf("%sは言います：ニャー!\n", name);
    }
};

// ===== Bird クラス =====
class Bird : public Animal {
public:
    Bird(const char* n) : Animal(n) {}

    void speak() override {
        printf("%sは言います：チュン!\n", name);
    }
};

int main() {
    system("chcp 65001 > nul");

    Animal* animals[3];
    animals[0] = new Dog("レックス");
    animals[1] = new Cat("ミミ");
    animals[2] = new Bird("ピヨ");

    int count = sizeof(animals) / sizeof(animals[0]);

    for (int i = 0; i < count; i++) {
        animals[i]->speak();  // 同じ呼び出し、異なる動作
    }

    // メモリ解放
    for (int i = 0; i < count; i++) {
        delete animals[i];
    }

    return 0;
}