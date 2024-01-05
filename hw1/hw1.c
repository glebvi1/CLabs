#include <stdio.h>
#include <math.h> // Подключение модуля для работы с математикой
#include <windows.h>

int main() {
    // Меняем кодировку на UTF-8, чтобы можно было писать на русском
    SetConsoleOutputCP(CP_UTF8);

    int x, y;
    double z, a, b;

    // Ввод переменных. Дружественный интерфейс
    printf("Выполнил задание: Вязов Глеб. Группа: БПМ231\n");
    printf("Введите значение x (целое): ");
    scanf("%d", &x);
    printf("Введите значение y (целое): ");
    scanf("%d", &y);

    printf("Введите значение z (дробное): ");
    scanf("%lf", &z);

    // Считаем значение a
    a = log(fabs(
            (y-sqrt(abs(x)))*
            (x - y / (double) (abs(x) + pow(x, 2) / (double) 4))
            ));

    // Считаем значение b
    b = x - (pow(x, 2) / (double) (1*2*3))
            + (pow(x, 5) / (double) (1*2*3*4*5));

    // Вывод
    printf("\nx =%10d\ny =%10d\nz =%10.5e\n", x, y, z);
    printf("\na =%10.4lf\nb =%10.4lf\n", a, b);

    // Вывод x(8)
    printf("\nx(8) =%o", x);

    // Вывод y(16)
    printf("\ny(16) =%x", y);

    return 0;
}
