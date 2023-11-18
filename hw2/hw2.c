#include <stdio.h>

int isBelongs(double x, double y) {
    return (y <= x / 2.0 && x*x + y*y <= 1) || (y == x / 2.0);
}

int main() {
    // Меняем кодировку на UTF-8, чтобы можно было писать на русском
    system("chcp 65001");

    double x, y;

    // Ввод переменных. Дружественный интерфейс
    printf("Выполнил задание: Вязов Глеб. Группа: БПМ231\n");
    printf("Введите значение x (дробное): ");
    scanf("%lf", &x);
    printf("Введите значение y (дробное): ");
    scanf("%lf", &y);

    // 1 способ
    if (y == x / 2.0) {
        printf("ДА");
    } else if (y < x / 2.0) {
        if (x*x + y*y <= 1) {
            printf("ДА");
        } else {
            printf("НЕТ");
        }
    } else {
        printf("НЕТ");
    }
    printf("\n");

    // 2 способ
    if ((y < x / 2.0 && x*x + y*y <= 1)
        || (y == x / 2.0)) {
        printf("ДА");
    } else {
        printf("НЕТ");
    }
    printf("\n");

    // 3 способ
    if (isBelongs(x, y)) {
        printf("ДА");
    } else {
        printf("НЕТ");
    }

    return 0;
}
