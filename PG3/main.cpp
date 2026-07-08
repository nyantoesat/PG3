#include <iostream>
using namespace std;

// ===== 基底クラス：Animal =====
class Animal {
public:
	const char* name;

	Animal(const char* n) : name(n) {} // コンストラクタ

	virtual void speak() { // 仮想関数
		cout << name << "は言います：..." << endl;
	}

	virtual ~Animal() {} // 仮想デストラクタ
};

// ===== Dog クラス =====
class Dog : public Animal {
public:
	Dog(const char* n) : Animal(n) {} // 親のコンストラクタを呼ぶ

	void speak() override { cout << name << "は言います：ワン！" << endl; }
};

// ===== Cat クラス =====
class Cat : public Animal {
public:
	Cat(const char* n) : Animal(n) {}

	void speak() override { cout << name << "は言います：ニャー！" << endl; }
};

// ===== Bird クラス =====
class Bird : public Animal {
public:
	Bird(const char* n) : Animal(n) {}

	void speak() override { cout << name << "は言います：チュン！" << endl; }
};

// ===== メイン：インスタンスを生成して実例を示す =====
int main() {
	system("chcp 65001 > nul");

	Animal* animals[3];
	animals[0] = new Dog("レックス");
	animals[1] = new Cat("ミミ");
	animals[2] = new Bird("ピヨ");

	int count = sizeof(animals) / sizeof(animals[0]);

	for (int i = 0; i < count; i++) {
		animals[i]->speak(); // 同じ呼び出し、異なる動作
	}

	// メモリ解放
	for (int i = 0; i < count; i++) {
		delete animals[i];
	}

	return 0;
}