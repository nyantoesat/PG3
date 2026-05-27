#include <iostream>
#include <functional>
#include <ctime>
#include <Windows.h>

using namespace std;

void SetTimeout(int ms, function<void()> callback) {
    Sleep(ms);
    callback();
}

int main() {
    SetConsoleOutputCP(65001);
    srand((unsigned)time(NULL));

    int user;
    cout << "奇数なら1、偶数なら0を入力: ";
    cin >> user;

    int dice = rand() % 6 + 1;
    cout << "出目は " << dice << endl;
    cout << "結果は・・・" << endl;

    SetTimeout(3000, [dice, user]() {
        if (dice % 2 == user) {
            cout << "正解" << endl;
        }
        else {
            cout << "不正解" << endl;
        }
        });

    return 0;
}