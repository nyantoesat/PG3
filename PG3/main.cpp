#include <stdio.h>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cnd;
int turn = 1; // 次に表示していいスレッド番号

int main() {
    auto printThread = [](int id) {
        std::unique_lock<std::mutex> lock(mtx);
        cnd.wait(lock, [id] { return turn == id; }); // 自分の番が来るまで待機（sleepは使わない）

        printf("thread %d\n", id);

        turn++;
        cnd.notify_all(); // 他の待機中スレッドに通知
        };

    std::thread th1(printThread, 1);
    std::thread th2(printThread, 2);
    std::thread th3(printThread, 3);

    th1.join();
    th2.join();
    th3.join();

    return 0;
}