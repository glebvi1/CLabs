#ifndef HW8_STRUCTS_H
#define HW8_STRUCTS_H

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

void findSportsmensByFIO(char fio[]);
void findSportsmensByAge(int age);
void findSportsmensByHeight(int height);
void findSportsmensByWeight(int weight);
void findSportsmensByType(char type[]);
void findSportsmensByRank(char rank[]);

#endif