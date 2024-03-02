#include <stdlib.h>
#include "repository.c"

/*
 * Для всех сортировок: параметр ascending отвечает за порядок сортировки
 * Если ascending = 1, то сортировка по возрастанию
 * Если ascending = -1, то сортировка по убыванию
 */

// Сортировка вставками. Время: O(n^2). Память: O(1)
void insertSort(struct Sportsmen array[], int len, int ascending) {
    struct Sportsmen value;
    int j;

    for (int i=1; i<len; i++) {
        value = array[i];

        for (j=i-1; j >= 0; j--) {
            if (ascending*compareSportsmens(array[j], value) == 1) {
                array[j+1] = array[j];
            } else {
                break;
            }
        }

        array[j+1] = value;
    }
}

// Вспомогательная функция для сортировки слиянием
void merge(struct Sportsmen array[], int l, int m, int r, int ascending) {
    int len1 = m - l + 1;
    int len2 = r - m;
    struct Sportsmen* left = calloc(len1, sizeof(struct Sportsmen));  // [l, m]
    struct Sportsmen* right = calloc(len2, sizeof(struct Sportsmen)); // [m+1, r]
    int i = l, i1=0, i2=0; // i -- индекс для array, i1 -- индекс для left, i2 -- индекс для right

    // Заполняем левые и правые части массивов элементами исходного
    for (int k=l; k<=m; k++) {
        left[k-l] = array[k];
    }
    for (int k=m+1; k<=r; k++) {
        right[k-(m+1)] = array[k];
    }

    // Алгоритм сортировки
    while (i1 < len1 && i2 < len2) {
        if (ascending*compareSportsmens(right[i2], left[i1]) == 1) { // right[i2] >= left[i1]
            array[i] = left[i1];
            i1++;
        } else {
            array[i] = right[i2];
            i2++;
        }
        i++;
    }

    // Один из индексов может не дойти до конца
    while (i1 < len1) {
        array[i] = left[i1];
        i++;
        i1++;
    }

    while (i2 < len2) {
        array[i] = right[i2];
        i++;
        i2++;
    }

    free(left);
    free(right);
}

// Сортировка слиянием. Время: O(nlog n). Память: O(n)
// Сортируемый диапозон: array[l], ..., array[r] (все границы включены)
void mergeSort(struct Sportsmen array[], int l, int r, int ascending) {
    if (r <= l) {
        return;
    }

    int m = l + (r - l) / 2;
    mergeSort(array, l, m, ascending);
    mergeSort(array, m+1, r, ascending);
    merge(array, l, m, r, ascending);
}

// Вспомогательная функция для быстрой сортировки
// Меняет местами значения a и b
void swap(struct Sportsmen* a, struct Sportsmen* b) {
    struct Sportsmen temp = *a;
    *a = *b;
    *b = temp;
}

// Вспомогательная функция для быстрой сортировки
// Возвращает индекс "разделяющего" элемента
// Слева от "разделяющего" элемента находятся элементы, которые меньше его, а справа, которые больше
int partition(struct Sportsmen array[], int l, int r, int ascending) {
    struct Sportsmen pivot = array[l];
    int i = l, j = r;

    while (i < j) {
        if (ascending == 1) {
            // Находим индекс элемента, который больше pivot: pivot >= array[i]
            while (compareSportsmens(pivot, array[i]) == 1 && i <= r - 1) { i++; }
            // Находим индекс элемента, который меньше pivot: array[j] >= pivot
            while (compareSportsmens(array[j], pivot) == 1 && j >= l + 1) { j--; }
        } else {
            // Находим индекс элемента, который меньше pivot: array[i] >= pivot
            while (compareSportsmens(array[i], pivot) == 1 && i <= r - 1) { i++; }
            // Находим индекс элемента, который больше pivot: pivot >= array[j]
            while (compareSportsmens(pivot, array[j]) == 1 && j >= l + 1) { j--; }
        }

        if (i < j) {
            swap(&array[i], &array[j]);
        }
    }
    // Возвращаем на место разделяющий элемент
    swap(&array[l], &array[j]);
    return j;
}

// Быстрая сортировка. Время: O(nlog n). Память: O(1)
void quickSort(struct Sportsmen array[], int l, int r, int ascending) {
    if (l >= r) {
        return;
    }

    // Выбираем разделяющий элемент
    int partitionIndex = partition(array, l, r, ascending);

    quickSort(array, l, partitionIndex - 1, ascending);
    quickSort(array, partitionIndex + 1, r, ascending);
}