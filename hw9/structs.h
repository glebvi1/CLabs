#ifndef HW9_STRUCTS_H
#define HW9_STRUCTS_H

# define N 50

struct Sportsmen {
    char fio[N];  // ФИО
    int age;      // Возраст
    int height;   // Рост
    int weight;   // Вес
    char type[N]; // Вид спорта
    char rank[N]; // Спотртивное звание
};

void printSportsmen(struct Sportsmen sportsmen);
void printArrayOfSportsmen(struct Sportsmen sportsmen[], int len);
int compareSportsmens(struct Sportsmen sportsmen1, struct Sportsmen sportsmen2);
struct Sportsmen* generateSportmens(int count);
int random(int min, int max);

#endif