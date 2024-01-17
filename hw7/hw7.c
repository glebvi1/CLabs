#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define LEN 300

char* get_unique_char(char* word, int len) {
    int i, k = 0;
    for (i=0; i<len; i++) {
        // Поиск первого вхождения буквы word[i] в слово word.
        // Возвращает указатель на первое вхождение символа в строке
        // Сравниваем указателем на текущую букву
        if (strchr(word, word[i]) != &word[i]) {
            k++;
        } else {
            word[i-k] = word[i];
        }
    }
    word[i-k] = '\0';
    word = realloc(word, (i-k) * sizeof(char));
    return word;
}

// Фукнция создает строку (массив символов) на основе string
// Значения: string[first_index], ..., string[last_index-1]
// Длина слова: last_index - first_index
char* create_string(char string[], int first_index, int last_index) {
    char *word = calloc(last_index - first_index, sizeof(char));
    for (int i=first_index; i<last_index; i++) {
        word[i-first_index] = string[i];
    }
    return word;
}

// Функция возвращает последнее слово -- указатель на массив символов
char* get_last_word(char string[], int* len_string) {
    int index = 0;
    int first_index = 0;

    // Находим длину строки - 1 (index) и индекс, с которого начинается последнее слово (first_index)
    while (string[index] != '.') {
        if (string[index] == ' ') {
            first_index = index + 1;
        }
        index++;
    }

    // Сохраняю длину массива (не учитывая точку) и создаю массив символов -- последнее слово
    *len_string = index;
    return create_string(string, first_index, index);
}

void task(char string[], char* last_word, int len_string) {
    /* 1. Переменная first_index отвечает за первый индекс в слове. Прохожусь циклом по исходной строке.
     * 2. Если наткнулся на пробел, то создаю слово word: string[first_index], ..., string[i-1]
     * 3. Сравниваю с последним. Если равны (то есть strcmp = 0), то пропускаю его
     * 4. Вывожу только первые вхождения каждой буквы с помощью функции print_unique_char()
     */
    int first_index = 0;

    for (int i=0; i<len_string+1; i++) {
        if (string[i] == ' ') {
            // Обработка случая нескольких пробелов подрят
            if (string[first_index] == ' ') {
                first_index = i + 1;
                printf(" ");
                continue;
            }

            char* word = create_string(string, first_index, i);
            if (strcmp(last_word, word) == 0) { // Слова равны
                first_index = i + 1;
                continue;
            }

            char* unique_string = get_unique_char(word, i-first_index);
            printf(" %s", unique_string);

            first_index = i + 1;

            free(unique_string);
        }
    }
    printf(".");
}

int main() {
    // Меняем кодировку на UTF-8, чтобы можно было писать на русском
    SetConsoleOutputCP(CP_UTF8);
    // Ввод переменных. Дружественный интерфейс
    printf("Выполнил задание: Вязов Глеб. Группа: БПМ231\n");

    char string[LEN];
    int len_string;

    // Считываем строку из стандартного потока stdin
    gets(string);
    printf("Введённая строка: %s", string);

    char *last_word = get_last_word(string, &len_string);
    printf("\nПоследнее слово: %s", last_word);
    printf("\nОтвет:");
    task(string, last_word, len_string);

    printf("\nИзначальная строка (неизмененная): %s", string);

    free(last_word);

    return 0;
}
