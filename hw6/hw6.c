#include <stdio.h>
#include <stdlib.h>

// Функция возвращает индекс первого максимального элемента
int first_max_index(double *array, int k) {
    double max = array[0];
    int max_index = 0;

    for (int i=1; i<k; i++) {
        if (array[i] > max) {
            max = array[i];
            max_index = i;
        }
    }

    return max_index;
}

// Функция возвращает индекс последнего минимального элемента
int last_min_index(double *array, int k) {
    double min = array[0];
    int min_index = 0;

    for (int i=1; i<k; i++) {
        if (array[i] <= min) {
            min = array[i];
            min_index = i;
        }
    }

    return min_index;
}

// Функция сдвигает элементы на один влево, начиная с index
void move_elements(double *array, int k, int index) {
    for(int i=index; i<k-1; i++) {
        array[i] = array[i + 1];
    }
}

// Функция удаляет элементы
// Возвращает 0, если ни один из элементов не удалился
// Иначе, возвращает длину нового массива
int delete(double *array, int k) {
    int first = first_max_index(array, k);
    int last = last_min_index(array, k);
    int count_delete_elements = 0;
    // Если первый индекс указывает на один из двух последних элементов (k-1 или k-2)
    // Или последний индекс указывает на один из двух первыв элементов (0 или 1)
    // То в этом массиве ничего удалять не нужно
    if (first >= k-2 || last <= 1) {
        return 0;
    }

    int index = first+1;
    while (index < last) {
        if (array[index] <= 0) {
            index++;
        }

        move_elements(array, k, index);
        last--;
        count_delete_elements++;
    }

    array = realloc(array, (k-count_delete_elements) * sizeof(double));
    return k-count_delete_elements;
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
    int new_size = delete(array, k);

    // После realloc память может выделиться некорректно
    if (array == NULL) {
        return 1;
    }
    printf("\nПреобразованный массив: ");

    if (new_size != 0) {
        print_array(array, new_size);
    } else {
        print_array(array, k);
    }

    return 0;
}
