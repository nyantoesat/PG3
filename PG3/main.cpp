#include <stdio.h>
#include <stdlib.h>


typedef struct Animal {
    const char* name;
    void (*speak)(struct Animal* self);  
} Animal;


void dog_speak(Animal* self) {
    printf("%sは言います：ワン！\n", self->name);
}
Animal new_dog(const char* name) {
    Animal a;
    a.name = name;
    a.speak = dog_speak;
    return a;
}

// ===== Cat クラス =====
void cat_speak(Animal* self) {
    printf("%sは言います：ニャー！\n", self->name);
}
Animal new_cat(const char* name) {
    Animal a;
    a.name = name;
    a.speak = cat_speak;
    return a;
}


void bird_speak(Animal* self) {
    printf("%sは言います：チュン！\n", self->name);
}
Animal new_bird(const char* name) {
    Animal a;
    a.name = name;
    a.speak = bird_speak;
    return a;
}

int main(void) {
    system("chcp 65001 > nul");
    Animal animals[3];
    animals[0] = new_dog("レックス");
    animals[1] = new_cat("ミミ");
    animals[2] = new_bird("ピヨ");

    int count = sizeof(animals) / sizeof(animals[0]);

    for (int i = 0; i < count; i++) {
        animals[i].speak(&animals[i]); 
    }

    return 0;
}