#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <functional>
#include <string>


void SetTimeout(std::function<void()> callback, int milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    callback();
}

int main()
{
    // 日本語表示のため (Windows コンソール)
    setlocale(LC_ALL, "");

    // ------------------------------------------------------
    // [条件1] 抽選結果をランダムで決定 (1〜6 のサイコロ)
    // ------------------------------------------------------
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dice(1, 6);
    int diceResult = dice(gen);

    // ------------------------------------------------------
    // [条件2] ユーザーから入力を受け取る
    //   1 = 半(奇数) / 2 = 丁(偶数)
    // ------------------------------------------------------
    std::cout << "===== サイコロ 半丁ゲーム =====" << std::endl;
    std::cout << "サイコロを振ります。出目が 半(奇数) か 丁(偶数) か当ててください。" << std::endl;
    std::cout << "  1: 半 (奇数)" << std::endl;
    std::cout << "  2: 丁 (偶数)" << std::endl;
    std::cout << "入力 > ";

    int userInput = 0;
    std::cin >> userInput;

    // 入力チェック
    if (userInput != 1 && userInput != 2) {
        std::cout << "1 または 2 を入力してください。" << std::endl;
        return 0;
    }

    std::cout << "結果は ..." << std::endl;

    // ------------------------------------------------------
    // [条件4] ラムダ式で userInput と diceResult をキャプチャ
    //   この judge ラムダが結果判定処理を行う関数となる
    //   ※キャプチャ [=] により値コピーで取り込まれる
    // ------------------------------------------------------
    auto judge = [=]() {
        bool diceIsOdd = (diceResult % 2 == 1); // 奇数なら true
        bool userPickedOdd = (userInput == 1);      // 半(奇数)を選んだか

        std::cout << "サイコロの出目: " << diceResult
            << " (" << (diceIsOdd ? "半 / 奇数" : "丁 / 偶数") << ")"
            << std::endl;

        std::cout << "あなたの予想: "
            << (userPickedOdd ? "半 (奇数)" : "丁 (偶数)")
            << std::endl;

        if (diceIsOdd == userPickedOdd) {
            std::cout << ">>> あたり！おめでとうございます！ <<<" << std::endl;
        }
        else {
            std::cout << ">>> はずれ！残念！ <<<" << std::endl;
        }
    };

 
    SetTimeout(judge, 3000);

    std::cout << std::endl << "Enter キーで終了..." << std::endl;
    std::cin.ignore();
    std::cin.get();

    return 0;
}