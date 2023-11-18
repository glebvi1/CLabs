#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Поиск минимального элемента в вещественном массиве, длиной k, большего x
// Если такого элемента нет (то есть a_i <= x для всех i), то возвращается NAN
double find_min_element(double *array, int k, double x) {
    double min = array[0];
    for (int i=1; i < k; i++) {
        if (array[i] > x && (array[i] < min || min <= x)) {
            min = array[i];
        }
    }
    if (min <= x) {
        return NAN;
    }
    return min;
}

// Функция возвращает индекс последнего максимального элемента
int last_index_max_element(double *array, int k) {
    double max = array[0];
    int index_max = 0;

    for (int i=0; i<k; i++) {
        if (max <= array[i]) {
            max = array[i];
            index_max = i;
        }
    }

    return index_max;
}

// Функция считает среднее арифметическое, расположенных до последнего максимального элемента
double mean(double *array, int k) {
    double sum = 0;
    int current_len = last_index_max_element(array, k);
    if (current_len == 0) {
        return 0;
    }

    for (int i=0; i < current_len; i++) {
        sum += array[i];
    }

    return sum / current_len;
}

// Выделение памяти для массива из k элементов
double* get_memory(int* k) {
    printf("Введите длину массива: ");
    scanf("%d", k);

    // Выделение памяти для k элементов, размерности sizeof(double)
    // И инициализируем всё нулями
    double *array = calloc(*k, sizeof(double));
    return array;
}

// Заполнение массива, длиной k, вещественными элементами
double * create_array(double *array, int k) {
    for (int i=0; i<k; i++) {
        scanf("%lf", &array[i]);
    }
    return array;
}

// Вывод массива длиной k с вещественными элементами
void print_array(double *array, int k) {
    for (int i=0; i<k; i++) {
        printf("%10.4lf\t", array[i]);
    }
}

int main() {
    // Меняем кодировку на UTF-8, чтобы можно было писать на русском
    system("chcp 65001");
    // Ввод переменных. Дружественный интерфейс
    printf("Выполнил задание: Вязов Глеб. Группа: БПМ231\n");

    unsigned int k;
    double *array = get_memory(&k);

    // Если память не выделилась -- возвращаем ошибку
    if (array == NULL) {
        return 1;
    }
    create_array(array, k);
    printf("Вы создали массив: ");
    print_array(array, k);

    double min = find_min_element(array, k, 0);
    if (isnan(min)) {
        printf("\nМинимальный элемент, больший 0: такого нет :(");
    } else {
        printf("\nМинимальный элемент, больший 0: %10.4lf", min);
    }
    printf("\nСреднее арифметическое до последнего максимального элемента: %10.4lf", mean(array, k));

    // Освобождаем память
    free(array);

    return 0;
}
