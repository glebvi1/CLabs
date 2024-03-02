#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

#define LEN_FIOS 18
#define LEN_TYPES 15
#define LEN_RANKS 14

const char FIOS[LEN_FIOS][N] = {
        "Иван Иванов", "Павел Артемьев", "Емельяненко Федор",
        "Арнольд Шварцнегер", "Луговой Александр", "Сарычев Кирилл", "Джулиус Мэддокс",
        "Тайсон Майк", "Попович Алеша", "Муромец Илья", "Добрыня Никитич", "Ронни Колман",
        "Цзю Константин", "Хабиб", "Конор Макгрегор", "Фишер Роберт", "Карякин Сергей",
        "Магнус Карлсен"
};
const char TYPES[LEN_TYPES][N] = {
        "Тяжелая атлетика", "ММА", "Бокс", "Самбо", "Дзюдо", "Пауэрлифтинг",
        "Легкая атлетика", "АРБ", "Кикбоксинг", "Тайский бокс", "БЖЖ",
        "Бодибилдинг", "Шахматы", "Водное поло", "Плавание"
};
const char RANKS[LEN_RANKS][N] = {
        "ЧМ", "МСМК", "ЗМС", "МС", "КМС", "1 взрослый разряд", "2 взрослый разряд",
        "3 взрослый разряд", "1 юношеский разряд", "2 юношеский разряд", "3 юношеский разряд",
        "Любитель", "Просто за ЗОЖ", "Олимпиец"
};

// Вывод спортсмена в консоль
void printSportsmen(struct Sportsmen sportsmen) {
    printf("%s, %d, %d, %d, %s, %s\n", sportsmen.fio, sportsmen.age, sportsmen.height, sportsmen.weight,
           sportsmen.type, sportsmen.rank);
}

// Вывод массива спортсменов в консоль
void printArrayOfSportsmen(struct Sportsmen sportsmen[], int len) {
    for (int i=0; i<len; i++) {
        printSportsmen(sportsmen[i]);
    }
    printf("\n");
}

// Функция сравнивает двух спортсменов
// Возвращает 1, если sportsmen1 >= sportsmen2
// Возвращает -1, если sportsmen1 < sportsmen2
int compareSportsmens(struct Sportsmen sportsmen1, struct Sportsmen sportsmen2) {
    // Сравнение ФИО
    int compareFio = strcmp(sportsmen1.fio, sportsmen2.fio);
    if (compareFio > 0) {
        return 1;
    } else if (compareFio < 0) {
        return -1;
    }

    // Сравнение возраста
    if (sportsmen1.age > sportsmen2.age) {
        return 1;
    } else if (sportsmen1.age < sportsmen2.age) {
        return -1;
    }

    // Сравнение роста
    if (sportsmen1.height > sportsmen2.height) {
        return 1;
    } else if (sportsmen1.height < sportsmen2.height) {
        return -1;
    }

    // Сравнение веса
    if (sportsmen1.weight > sportsmen2.weight) {
        return 1;
    } else if (sportsmen1.weight < sportsmen2.weight) {
        return -1;
    }

    // Сравнение вида спорта
    int compareType = strcmp(sportsmen1.type, sportsmen2.type);
    if (compareType > 0) {
        return 1;
    } else if (compareType < 0) {
        return -1;
    }

    // Сравнение спортивного звания
    int compareRank = strcmp(sportsmen1.rank, sportsmen2.rank);
    if (compareRank > 0) {
        return 1;
    } else if (compareRank < 0) {
        return -1;
    }

    // Объекты равны
    return 1;
}

// Генерация пвесво-рандомного числа из диапозона [min; max]
int random(int min, int max) {
    return min + rand()%(max-min);
}

// Функция генерирует массив из спортсменов длиной count
struct Sportsmen* generateSportmens(int count) {
    struct Sportsmen* sportsmens = calloc(count, sizeof(struct Sportsmen));

    for (int i=0; i<count; i++) {
        struct Sportsmen sp;
        strcpy(sp.fio, FIOS[random(0, LEN_FIOS-1)]);
        sp.age = random(18, 60),
        sp.height = random(160, 210),
        sp.weight = random(50, 170),
                strcpy(sp.type, TYPES[random(0, LEN_TYPES-1)]);
        strcpy(sp.rank, RANKS[random(0, LEN_RANKS-1)]);

        sportsmens[i] = sp;
    }
    return sportsmens;
}
