#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

char* assembly(char x1, char x2, char x3) {
    char y1 = x1 - '0', y2 = x2 - '0', y3 = x3 - '0';

    __asm__ (
            ".intel_syntax noprefix \n\t"       // Меняем синтаксис AT&T на синтаксис Intel

            // Сохраняем в память переменные и считаем сумму
            "mov al, %0             \n\t"       // al = x1
            "mov bl, %1             \n\t"       // bl = x2
            "mov cl, %2             \n\t"       // cl = x3
            "add al, cl             \n\t"       // al = al + cl = x1 + x3

            // Условие: сравниваем al == bl
            "cmp al, bl             \n\t"
            "je INACE               \n\t"       // Если al == cl, то переходим на метку INACE

            // Если вторая цифра НЕ равна сумме первой и третей, то меняем местами первые две цифры (al != cl)
            "mov %1, %0             \n\t"       // y2 = x1
            "mov %0, bl             \n\t"       // y1 = x2
            "jmp EXIT               \n\t"

            // Если вторая цифра равна сумме первой и третей, то y2 = 9 - x2 (al == cl)
            "INACE:                 \n\t"       // Переходим на метку INACE1
            "sub bl, 9              \n\t"       // bl = 9 - bl <= 0
            "neg bl                 \n\t"       // bl = -bl
            "mov %1, bl             \n\t"       // y2 = bl = 9 - x2

            // Выход
            "EXIT:                  \n\t"       // метка выхода
            "nop                    \n\t"
            ".att_syntax prefix;    \n\t"

            : "=r"(y1), "=r"(y2), "=r"(y3)      // выходной оператор: y1=%0, y2=%1, y3=%2
            : "0"(y1), "1"(y2), "2"(y3)         // входной оператор: x1=%3, x2=%4, x3=%5
            : "eax"                             // список разрушаемых объектов
            );

    y1 += '0', y2 += '0', y3 += '0';

    char *res = calloc(3, sizeof(char));
    res[0] = y1, res[1] = y2, res[2] = y3;

    return res;
}

char* fun(char x1, char x2, char x3) {
    char y1, y2, y3;

    if ((x2-'0') == (x1-'0') + (x3-'0')) {
        y1 = x1, y2 = (9 - (x2 - '0')) + '0', y3 = x3;
    } else {
        y1 = x2, y2 = x1, y3 = x3;
    }

    char *res = calloc(3, sizeof(char));
    res[0] = y1, res[1] = y2, res[2] = y3;

    return res;
}

int main() {
    // Меняем кодировку на UTF-8, чтобы можно было писать на русском
    SetConsoleOutputCP(CP_UTF8);
    // Ввод переменных. Дружественный интерфейс
    printf("Выполнил задание: Вязов Глеб. Группа: БПМ231\n");

    char x1, x2, x3; // байты
    char string[3];

    fgets(string, 4, stdin);
    printf("Введенная строка: %s", string);
    x1 = string[0], x2 = string[1], x3 = string[2];

    if (!(isdigit(x1) && isdigit(x2) && isdigit(x3))) {
        printf("\nНекорректный ввод!");
        return 0;
    }

    printf("\nОтвет на C: %s", fun(x1, x2, x3));
    printf("\nОтвет на ассемблере: %s", assembly(x1, x2, x3));

    return 0;
}

/*
 *     __asm__ (
            ".intel_syntax noprefix \n\t"       // Меняем синтаксис AT&T на синтаксис Intel

            "mov al, %3             \n\t"       // al = x1
            "mov cl, %5             \n\t"       // cl = x3
            "add al, cl             \n\t"       // al = al + cl = x1 + x3
            "mov bl, %4             \n\t"       // bl = x2
            // Условие: сравниваем al == bl
            "cmp al, bl             \n\t"
            "je INACE               \n\t"       // Если al == cl, то переходим на метку INACE

            // Если вторая цифра НЕ равна сумме первой и третей, то меняем местами первые две цифры (al != cl)
            "mov %0, bl             \n\t"       // y1 = x2
            "mov %1, cl             \n\t"       // y2 = x1
            "jmp EXIT               \n\t"

            // Если вторая цифра равна сумме первой и третей, то y2 = 9 - x2 (al == cl)
            "INACE:                 \n\t"       // Переходим на метку INACE
            "sub bl, 9              \n\t"       // bl = 9 - bl <= 0
            "neg bl                 \n\t"       // bl = -bl
            "mov %0, %3             \n\t"       // y1 = x1
            "mov %1, bl             \n\t"       // y2 = bl = 9 - x2
            "jmp EXIT               \n\t"

            // Выход
            "EXIT:                  \n\t"
            "mov %2, %5             \n\t"       // y3 = x3
            ".att_syntax prefix;    \n\t"

            : "=&r"(y1), "=&r"(y2), "=&r"(y3)   // выходной оператор: y1=%0, y2=%1, y3=%2
            : "r"(x1), "r"(x2), "r"(x3)         // входной оператор: x1=%3, x2=%4, x3=%5
            : "eax"                             // список разрушаемых объектов
            );
 */
