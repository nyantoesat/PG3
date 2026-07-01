#include<stdio.h>
#include <cstdlib>
#include <cstring>
#include <Windows.h>
#include<list>

void printList(const std::list<const char*>& lst)
{
	for (const char* station : lst)
	{
		printf("%s\n", station);
	}
}

int main()
{
	system("chcp 65001 > nul");
	std::list<const char*> stationList = {
		"Shinagawa",
		"Osaki",
		"Gotanda",
		"Meguro",
		"Ebisu",
		"Shibuya",
		"Harajuku",
		"Yoyogi",
		"Shinjuku",
		"Shin-Okubo",
		"Takadanobaba",
		"Mejiro",
		"Ikebukuro",
		"Otsuka",
		"Sugamo",
		"Komagome",
		"Tabata",
		"Nippori",
		"Uguisudani",
		"Ueno",
		"Okachimachi",
		"Akihabara",
		"Kanda",
		"Tokyo",
		"Yurakucho",
		"Shimbashi",
		"Hamamatsucho",
		"Tamachi"
	};

	printf("1970年の山手線駅の名前\n\n");
	printList(stationList);
	printf("\n");

	// 2019年: Nishi-Nippori を Nippori の次に追加
	printf("2019年の山手線駅の名前\n");
	auto it = stationList.begin();
	for (; it != stationList.end(); ++it)
	{
		if (strcmp(*it, "Nippori") == 0)
		{
			++it; // Nipporiの次（Uguisudani）を指す
			break;
		}
	}
	stationList.insert(it, "Nishi-Nippori"); // Uguisudaniの前 = Nipporiの次に挿入
	printList(stationList);
	printf("\n");

	// 2022年: Takanawa Gateway を Shinagawa の次に追加
	printf("2022年の山手線駅の名前\n");
	auto it2 = stationList.begin();
	for (; it2 != stationList.end(); ++it2)
	{
		if (strcmp(*it2, "Shinagawa") == 0)
		{
			++it2; // Shinagawaの次（Osaki）を指す
			break;
		}
	}
	stationList.insert(it2, "Takanawa Gateway"); // Osakaの前 = Shinagawaの次に挿入
	printList(stationList);

	return 0;
}