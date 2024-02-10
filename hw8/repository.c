#include <stdio.h>
#include <string.h>
#include "structs.h"

#define FILE_NAME "hw8/data.bin"

// Поиск спортсменов по ФИО
void findSportsmensByFIO(char fio[]) {
    FILE *fp;
    fp = fopen(FILE_NAME, "r");
    struct Sportsmen s;
    int result = 1;

    while (!feof(fp)) {
        if (fread(&s, sizeof(s), 1, fp) > 0 && strcmp(fio, s.fio) == 0) {
            printSportsmen(s);
            result = 0;
        }
    }
    printf("\n");
    fclose(fp);

    if (result) {
        printf("Таких спортсменов нет!");
    }
}

// Поиск спортсменов по возрасту
void findSportsmensByAge(int age) {
    FILE *fp;
    fp = fopen(FILE_NAME, "r");
    struct Sportsmen s;
    int result = 1;

    while (!feof(fp)) {
        if (fread(&s, sizeof(s), 1, fp) > 0 && s.age == age) {
            printSportsmen(s);
            result = 0;
        }
    }
    printf("\n");
    fclose(fp);

    if (result) {
        printf("Таких спортсменов нет!");
    }
}

// Поиск спортсменов по росту
void findSportsmensByHeight(int height) {
    FILE *fp;
    fp = fopen(FILE_NAME, "r");
    struct Sportsmen s;
    int result = 1;

    while (!feof(fp)) {
        if (fread(&s, sizeof(s), 1, fp) > 0 && s.height == height) {
            printSportsmen(s);
            result = 0;
        }
    }
    printf("\n");
    fclose(fp);

    if (result) {
        printf("Таких спортсменов нет!");
    }
}

// Поиск спортсменов по весу
void findSportsmensByWeight(int weight) {
    FILE *fp;
    fp = fopen(FILE_NAME, "r");
    struct Sportsmen s;
    int result = 1;

    while (!feof(fp)) {
        if (fread(&s, sizeof(s), 1, fp) > 0 && s.weight == weight) {
            printSportsmen(s);
            result = 0;
        }
    }
    printf("\n");
    fclose(fp);

    if (result) {
        printf("Таких спортсменов нет!");
    }
}

// Поиск спортсменов по виду спорта
void findSportsmensByType(char type[]) {
    FILE *fp;
    fp = fopen(FILE_NAME, "r");
    struct Sportsmen s;
    int result = 1;

    while (!feof(fp)) {
        if (fread(&s, sizeof(s), 1, fp) > 0 && strcmp(type, s.type) == 0) {
            printSportsmen(s);
            result = 0;
        }
    }
    printf("\n");
    fclose(fp);

    if (result) {
        printf("Таких спортсменов нет!");
    }
}

// Поиск спортсменов по спортивному званию
void findSportsmensByRank(char rank[]) {
    FILE *fp;
    fp = fopen(FILE_NAME, "r");
    struct Sportsmen s;
    int result = 1;

    while (!feof(fp)) {
        if (fread(&s, sizeof(s), 1, fp) > 0 && strcmp(rank, s.rank) == 0) {
            printSportsmen(s);
            result = 0;
        }
    }
    printf("\n");
    fclose(fp);

    if (result) {
        printf("Таких спортсменов нет!");
    }
}
