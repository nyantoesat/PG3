#include <iostream>
#include <ctime>
#include <Windows.h>

using namespace std;

typedef void (*Callback)();

void showCorrect() {
    cout << "正解" << endl;
}

void showWrong() {
    cout << "不正解" << endl;
}

void judge(int dice, int user, Callback cb) {
    cout << "結果は・・・" << endl;
    Sleep(3000);
    Callback results[2] = { showWrong, showCorrect };
    cb = results[dice % 2 == user];
    cb();
}

int main() {
    SetConsoleOutputCP(65001);
    srand((unsigned)time(NULL));

    int user;
    cout << "奇数なら1、偶数なら0を入力: ";
    cin >> user;

    int dice = rand() % 6 + 1;
    cout << "出目は " << dice << endl;

    Callback cb = NULL;
    judge(dice, user, cb);

    return 0;
}