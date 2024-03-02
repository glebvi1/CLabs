#include <time.h>
#include <windows.h>
#include "sorting.c"

const int sizes[] = {100, 1000, 5000, 10000, 20000, 50000, 100000};

int main() {
    // Меняем кодировку на UTF-8, чтобы можно было писать на русском
    SetConsoleOutputCP(CP_UTF8);

    double timeSpent;
    printf("Сортировка вставками:\n");
    for (int i=0; i<7; i++) {
        struct Sportsmen* sportsmens = generateSportmens(sizes[i]);

        clock_t begin = clock();
        insertSort(sportsmens, sizes[i], 1);
        clock_t end = clock();
        timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;

        printf("Длина массива = %5d, время работы = %10.4lf секунд\n", sizes[i], timeSpent);
    }

    printf("\nСортировка слиянием:\n");
    for (int i=0; i<7; i++) {
        struct Sportsmen* sportsmens = generateSportmens(sizes[i]);

        clock_t begin = clock();
        mergeSort(sportsmens, 0, sizes[i]-1, 1);
        clock_t end = clock();
        timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;

        printf("Длина массива = %5d, время работы = %10.4lf секунд\n", sizes[i], timeSpent);
    }

    printf("\nБыстрая сортировка:\n");
    for (int i=0; i<7; i++) {
        struct Sportsmen* sportsmens = generateSportmens(sizes[i]);

        clock_t begin = clock();
        quickSort(sportsmens, 0, sizes[i]-1, 1);
        clock_t end = clock();
        timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;

        printf("Длина массива = %6d, время работы = %10.4lf секунд\n", sizes[i], timeSpent);
    }

    return 0;
}
