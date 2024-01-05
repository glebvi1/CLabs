#include <stdio.h>
#include <windows.h>

int const NMAX = 100;

// Создаем массив
void create_array(int array[][NMAX], int *pm, int *pn) {
    printf("Введите количество строк массива: ");
    scanf("%d", pm);
    printf("Введите количество столбцов массива: ");
    scanf("%d", pn);

    for (int i=0; i<*pm; i++) {
        for (int j=0; j<*pn; j++) {
            scanf("%d", &array[i][j]);
        }
    }
}

// Вывод массива
void print_array(int array[][NMAX], int m, int n) {
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            printf("%d\t", array[i][j]);
        }
        printf("\n");
    }
}

// Функция возвращает максимальное количество четных чисел в строке
int max_even_in_line(int array[][NMAX], int m, int n) {
    int max_even = 0;
    for (int i=0; i<m; i++) {
        int current_max_even = 0;
        for (int j=0; j<n; j++) {
            if (array[i][j] % 2 == 0) {
                current_max_even++;
            }
        }

        // Если в этой строке четных элементов больше, то запоминаем
        if (current_max_even > max_even) {
            max_even = current_max_even;
        }
    }
    return max_even;
}

// Функция возвращает сумму элементов, та тех строках, на которых кол-во
// четных элементов максимально
int sum_max_even(int array[][NMAX], int m, int n) {
    int sum = 0;
    int max_even = max_even_in_line(array, m, n);

    for (int i=0; i<m; i++) {
        int current_max_even = 0;
        int current_sum = 0;

        for (int j=0; j<n; j++) {
            current_sum += array[i][j];
            if (array[i][j] % 2 == 0) {
                current_max_even++;
            }
        }

        // Если в этой строке количество четных элементов -- максимально
        // То добавляем сумму элементов на этой строке
        if (current_max_even == max_even) {
            sum += current_sum;
        }
    }

    return sum;
}

int main() {
    // Меняем кодировку на UTF-8, чтобы можно было писать на русском
    SetConsoleOutputCP(CP_UTF8);
    // Ввод переменных. Дружественный интерфейс
    printf("Выполнил задание: Вязов Глеб. Группа: БПМ231\n");

    int array[NMAX][NMAX];
    unsigned int m, n;

    create_array(array, &m, &n);
    printf("Вы создали массив:\n");
    print_array(array, m, n);
    printf("Сумма элементов тех строк, которые содержат наибольшее число чётных элементов: %d",
           sum_max_even(array, m, n));

    return 0;
}
