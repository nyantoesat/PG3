#include <stdio.h>
#include <Windows.h>

int RecursiveWage(int n) {
    if (n <= 1) {
        return (100);
    }
    return (RecursiveWage(n - 1) * 2 - 50);
}


int RecursiveTotal(int n) {
    if (n <= 0) {
        return (0);
    }
    return (RecursiveTotal(n - 1) + RecursiveWage(n));
}


int main() {

    system("chcp 65001>nul");
    SetConsoleOutputCP(65001);

    const int generalWage = 1072; 

    printf("時間 | 一般的賃金(合計) | 再帰的時給 | 再帰的賃金(合計)\n");
    printf("-----+------------------+------------+------------------\n");

    for (int hour = 1; hour <= 12; hour++) {
        int generalTotal = generalWage * hour;
        int recursiveHour = RecursiveWage(hour);
        int recursiveTotal = RecursiveTotal(hour);

        printf("%3d時間 | %12d円 | %8d円 | %12d円",
            hour, generalTotal, recursiveHour, recursiveTotal);

        if (recursiveTotal > generalTotal) {
            printf("  ← 再帰的賃金体系のほうが得");
        }
        printf("\n");
    }

    return (0);
}