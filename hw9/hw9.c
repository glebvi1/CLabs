#include <stdio.h>
#include <windows.h>
#include "sorting.c"

int main() {
    // Меняем кодировку на UTF-8, чтобы можно было писать на русском
    SetConsoleOutputCP(CP_UTF8);
    // Ввод переменных. Дружественный интерфейс
    printf("Выполнил задание: Вязов Глеб. Группа: БПМ231\n");

    int count, type_sorting, asc;

    printf("Введите длину массива, который будем сортировать: ");
    scanf("%d", &count);
    struct Sportsmen* sportsmens = generateSportmens(count);
    printArrayOfSportsmen(sportsmens, count);
    printf("Выберите алгоритм сортировки:\n"
           "1. Сортировка вставками\n"
           "2. Сортировка слиянием\n"
           "3. Быстрая сортировка\n");
    scanf("%d", &type_sorting);
    printf("Выберите направление сортировки:\n"
           "По возврастанию -- 1\n"
           "По убыванию -- -1\n");
    scanf("%d", &asc);
    switch (type_sorting) {
        case 1:
            insertSort(sportsmens, count, asc);
            break;
        case 2:
            mergeSort(sportsmens, 0, count-1, asc);
            break;
        case 3:
            quickSort(sportsmens, 0, count-1, asc);
            break;
    }
    printArrayOfSportsmen(sportsmens, count);
    free(sportsmens);
}
