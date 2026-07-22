#include <iostream>
#include <string>
#include <chrono>

int main() {
    system("chcp 65001 > nul");
    // 1,000,000文字の文字列型変数aを'a'で初期化
    std::string a(1000000, 'a');

    // ===== コピーにかかる時間の計測 =====
    auto copyStart = std::chrono::high_resolution_clock::now();
    std::string copied = a; // コピー
    auto copyEnd = std::chrono::high_resolution_clock::now();

    auto copyTime = std::chrono::duration_cast<std::chrono::microseconds>(copyEnd - copyStart);

    // ===== 移動にかかる時間の計測 =====
    auto moveStart = std::chrono::high_resolution_clock::now();
    std::string moved = std::move(a); // 移動
    auto moveEnd = std::chrono::high_resolution_clock::now();

    auto moveTime = std::chrono::duration_cast<std::chrono::microseconds>(moveEnd - moveStart);

    // ===== 結果の表示 =====
    std::cout << "コピーにかかった時間: " << copyTime.count() << " us" << std::endl;
    std::cout << "移動にかかった時間: " << moveTime.count() << " us" << std::endl;

    return 0;
}