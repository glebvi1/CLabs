#include <stdio.h>
#include <math.h>

// Функция считает сумму конечного числа для заданного количества членов ряда
double a_n_with_epsilon(double x) {
    double e;
    printf("\nВведите точность: ");
    scanf("%lf", &e);

    double a_n = 1;
    double summa = a_n;
    int i = 1;

    // Цикл работает пока модуль a_n элемента будет больше e
    // Как только мы достигнет заданной точности, цикл прервется
    while (fabs(a_n) > e) {
        a_n = a_n * x * (i+1) / i;
        summa += a_n;
        i++;
    }

    return summa;
}

// Функция считает сумму конечного числа с заданной точностью
double a_n_with_n(double x) {
    int n;
    printf("\nВведите количество членов ряда: ");
    scanf("%d", &n);

    double a_n = 1;
    double summa = a_n;

    // Цикл делает n-1 операцию
    // Первая операция уже сделана
    for (int i=1; i<n; i++) {
        a_n = a_n * x * (i+1) / i;
        summa += a_n;
    }

    return summa;
}

int main() {
    // Меняем кодировку на UTF-8, чтобы можно было писать на русском
    system("chcp 65001");

    int flag;
    double x;

    // Ввод переменных. Дружественный интерфейс
    printf("Выполнил задание: Вязов Глеб. Группа: БПМ231\n");
    printf("Введите x = ");
    scanf("%lf", &x);

    // Проверка x на корректность
    if (!(-1 < x && x < 1)) {
        printf("x не принадлежит промежутку (-1; 1)");
        return 0;
    }

    printf("По формуле = %lf", 1.0 / ((1-x)*(1-x)));

    // Ввод переменных. Дружественный интерфейс
    printf("\nВведите 1, если Вы хотите использовать цикл с заданной точностью");
    printf("\nВведите 2, если Вы хотите использовать цикл для заданного количества членов ряда: ");
    scanf("%d", &flag);

    // Оператор выбора swith-case-default
    switch (flag) {
        case 1: printf("%lf", a_n_with_epsilon(x)); break;
        case 2: printf("%lf", a_n_with_n(x)); break;
        default: printf("\nЯ не знаю такой команды :(");
    }

    return 0;
}