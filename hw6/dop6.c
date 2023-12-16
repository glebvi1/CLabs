#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

// Функция сдвигает элементы на один вправо, начиная с index
double* move_elements(double *array, int k, int index) {
    array = realloc(array, k * sizeof(double));
    for(int i=k-1; i>index; i--) {
        array[i] = array[i-1];
    }

    return array;
}

// Функция удаляет элементы
// Возвращает указатель на новое место в памяти
double* add(double *array, int k, int *new_size) {
    int size = k;
    int index = 0;

    while (index < size) {
        if (array[index] > 0) {
            size++;
            array = move_elements(array, size, index);
            index++;

            if (array == NULL) {
                return NULL;
            }
        }
        index++;
    }

    *new_size = size;
    return array;
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

    printf("\nПреобразованный: ");
    int new_size = k;
    double * new_array = add(array, k, &new_size);
    if (new_array != NULL) {
        print_array(new_array, new_size);
    }

}