#include <stdio.h>
#include <Windows.h>


template <typename Type>
Type Min(Type a, Type b) {
	return (a < b) ? a : b;
}

template <>
char Min<char>(char a, char b) {
	printf("数字以外は代入できません\n");
	return 0;
}

int main() {
	system("chcp 65001>nul");
	SetConsoleOutputCP(65001);
	printf("%d\n", Min<int>(114, 514));
	printf("%f\n", Min<float>(3.14, 2.71));
	printf("%lf\n",Min<double>(1.41, 2.71));
	printf("%c\n", Min<char>('N', 'Y'));
	return 0;
}