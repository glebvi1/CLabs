#include <stdio.h>
#include <windows.h>

short int assembly(short int x, char y, char z) {
    short int v = 0;

    __asm__(".intel_syntax noprefix \n" // Меняем синтаксис AT&T на синтаксис Intel
            // Вычисляем знаменатель
            "mov al, %3             \n" // al = z              (байт)
            "cbw                    \n" // ax = al             (слово)
            "mov bx, ax             \n" // bx = ax             (слово)
            "sub bx, 4              \n" // bx = bx - 4         (слово)                        (z - 4)
            // Вычисляем числитель
            "mov al, %2             \n" // al = y              (байт)
            "cbw                    \n" // ax = al             (слово)
            "add ax, 5              \n" // ax = ax + 5         (слово)                        (y + 5)
            "imul %1                \n" // dx = ax * x         (двойное слово)                x(y + 5)
            "sub ax, 3              \n" // ax = ax - 3         (слово, младшее слово)
            "sbb dx, 0              \n" // dx = dx - 0         (двойное слово, старшее слово) x(y + 5) - 3
            // Вычисляем дробь
            "idiv bx                \n" // ax = dx / bx        (слово)                        x(y + 5) - 3 / (z - 4)
            "add ax, 3              \n" // ax = ax + 3         (слово)
            "mov %0, ax             \n" // v = ax              (слово)
            ".att_syntax prefix;    \n"
            : "=r"(v)                // выходной оператор v --> %0
            : "r"(x), "r"(y), "r"(z) // входной оператор x --> %1, y --> %2, z --> %3
            : "eax"                  // список разрушаемых регистров
            );

    return v;
}

int main() {
    // Меняем кодировку на UTF-8, чтобы можно было писать на русском
    SetConsoleOutputCP(CP_UTF8);
    // Объявление переменных. Дружественный интерфейс
    printf("Выполнил задание: Вязов Глеб. Группа: БПМ231\n");
    char y, z; // байты
    short int x, v; // слова

    x = 0x2, y = -0x7, z = -0x3;
    v = ((x*(y+5) - 3) / (z-4)) + 3; // v=0x4
    short int res = assembly(x, y, z);

    printf("Первый тест: \n");
    printf("x=%d, y=%d, z=%d\n", x, y, z);
    printf("Ответ на C: v(10)=%d | v(16)=%xh \n", v, v);
    printf("Ответ на ассемблере: v(10)=%d | v(16)=%xh \n", res, res);

    x = 0x3FB5, y = 0x7D, z = -0x7E;
    v = ((x*(y+5) - 3) / (z-4)) + 3; // v=-0x3FB1
    res = assembly(x, y, z);

    printf("\nВторой тест: \n");
    printf("x=%d, y=%d, z=%d\n", x, y, z);
    printf("Ответ на C: v(10)=%d | v(16)=%xh \n", v, v);
    printf("Ответ на ассемблере: v(10)=%d | v(16)=%xh \n", res, res);
}
