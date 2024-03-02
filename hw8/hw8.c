#include <stdio.h>
#include <windows.h>
#include <unistd.h>
#include "repository.c"

#define option 0

void scanfSportsmen(struct Sportsmen *s);
void addSportsmen(struct Sportsmen sportsmen);
void deleteSportsmen(int index);
void updateSportsmen(int index, struct Sportsmen sportsmen);
void printFile();
void filter();
int getMaxHeight();

int main() {
    // Меняем кодировку на UTF-8, чтобы можно было писать на русском
    SetConsoleOutputCP(CP_UTF8);
    // Ввод переменных. Дружественный интерфейс
    printf("Выполнил задание: Вязов Глеб. Группа: БПМ231\n");

    FILE *fp;
    fp = fopen(FILE_NAME, "r");

    // Если файл не создан, то создаем
    if (fp == NULL) {
        printf("Такого файла нет!\n");
        fp = fopen(FILE_NAME, "wb");
        printf("Создан файл с именем %s!\n", FILE_NAME);
    }
    fclose(fp);

    // Заполняем данные из массива
#if option==0
    struct Sportsmen sportsmens[] = {
            {"Вязов Глеб", 17, 164, 56, "Шахматы", "3 разряд"},
            {"Иван Иванов Иванович", 23, 180, 84, "Тяжелая атлетика", "КМС"},
            {"Павел Артемьев", 43, 200, 120, "Паурлифтинг", "МСМК"},
            {"Емельяненко Федор", 35, 180, 80, "ММА", "ЧМ"},
            {"Арнольд Шварцнегер", 100, 180, 100, "Бодибилдинг", "ЧМ"},
            {"Луговой Александр", 40, 180, 56, "Пауэрлифтинг", "МСМК"},
            {"Сарычев Кирилл", 40, 200, 140, "Жим лежа", "МСМК"},
            {"Джулиус Мэддокс", 35, 170, 150, "Жим лежа", "ЧМ"},
            {"Сарычев Кирилл", 40, 200, 140, "Становая тяга", "МСМК"},
            {"Тайсон Майк", 57, 178, 80, "Бокс", "ЧМ"},
            };
    for (int i=0; i<10; i++) {
        addSportsmen(sportsmens[i]);
    }
    // Заполняем данные из консоли
#else
    int count;
    struct Sportsmen sp;
    printf("Количество записей: ");
    scanf("%d", &count);
    for (int i=0; i<count; i++) {
        scanfSportsmen(&sp);
        addSportsmen(sp);
    }
#endif
    printf("Вывести содержимое файла -- 0\n"
                  "Добавить запись в конец  -- 1\n"
                  "Удалить запись           -- 2\n"
                  "Обновить запись          -- 3\n"
                  "Поиск по полю структуры  -- 4\n"
                  "Завершить программу      -- 5\n");

    struct Sportsmen s;
    int index, flag = 1;

    printf("\nСамые высокие спортсмены:\n");
    int maxHeight = getMaxHeight();
    findSportsmensByHeight(maxHeight);

    while (flag) {
        int command;
        scanf("%d", &command);

        switch (command) {
            case 0: printFile(); break;
            case 1:
                scanfSportsmen(&s);
                addSportsmen(s);
                break;
            case 2:
                printf("\nВведите индекс: ");
                scanf("%d", &index);
                deleteSportsmen(index);
                break;
            case 3:
                scanfSportsmen(&s);
                printf("\nВведите индекс: ");
                scanf("%d", &index);
                updateSportsmen(index, s);
                break;
            case 4:
                filter();
                break;
            case 5:
                flag = 0;
        }
    }

    return 0;
}

// Функция вызывает функцию поиска в зависимости от введенных значений
void filter() {
    int command2, param2;
    char param1[N];

    printf("Введите номер поля:");
    scanf("%d", &command2);
    switch (command2) {
        case 0:
            printf("\nВведите ФИО: ");
            scanf("%s", param1);
            findSportsmensByFIO(param1);
            break;
        case 1:
            printf("\nВведите возраст: ");
            scanf("%d", &param2);
            findSportsmensByAge(param2);
            break;
        case 2:
            printf("\nВведите рост: ");
            scanf("%d", &param2);
            findSportsmensByHeight(param2);
            break;
        case 3:
            printf("\nВведите вес: ");
            scanf("%d", &param2);
            findSportsmensByWeight(param2);
            break;
        case 4:
            printf("\nВведите вид спорта: ");
            scanf("%s", param1);
            findSportsmensByType(param1);
            break;
        case 5:
            printf("\nВведите спортивное звание: ");
            scanf("%s", param1);
            findSportsmensByRank(param1);
            break;
    }
}

// Считать данные спортсмена через консоль
void scanfSportsmen(struct Sportsmen *s) {
    printf("\nВведите ФИО: ");
    fflush(stdin);
    gets(s->fio);
    printf("\nВведите возраст: ");
    scanf("%d", &s->age);
    printf("\nВведите рост: ");
    scanf("%d", &s->height);
    printf("\nВведите вес: ");
    scanf("%d", &s->weight);
    printf("\nВведите вид спорта: ");
    fflush(stdin);
    gets(s->type);
    printf("\nВведите спортивное звание: ");
    gets(s->rank);
}

// Вывод спортсмена в консоль
void printSportsmen(struct Sportsmen sportsmen) {
    printf("%s, %d, %d, %d, %s, %s\n", sportsmen.fio, sportsmen.age, sportsmen.height, sportsmen.weight,
           sportsmen.type, sportsmen.rank);
}

// Добавление спортсмена в конец файла
void addSportsmen(struct Sportsmen sportsmen) {
    FILE *fp;
    fp = fopen(FILE_NAME, "a");
    fwrite(&sportsmen, sizeof(sportsmen), 1, fp);
    fclose(fp);
}

// Удаление спортсмена по индексу. Индексация с нуля
void deleteSportsmen(int index) {
    FILE *fp;
    fp = fopen(FILE_NAME, "r+");

    // Считаем количество записей в файле
    fseek(fp, 0L, SEEK_END);
    int len = ftell(fp) / sizeof(struct Sportsmen);

    // Перемещаем курсор на index+1 позицию
    fseek(fp, (index+1)*sizeof(struct Sportsmen), SEEK_SET);
    struct Sportsmen s;

    for (int i=index; i<len-1; i++) {
        fread(&s, sizeof(s), 1, fp);              // cursor = i+1
        fseek(fp, i*sizeof(struct Sportsmen), SEEK_SET);     // cursor = i
        fwrite(&s, sizeof(struct Sportsmen), 1, fp);      // cursor = i --> cursor = i+1
        fseek(fp, (i+2)*sizeof(struct Sportsmen), SEEK_SET); // cursor = i+2
    }

    // Уменьшаем размер файла
    _chsize( fileno(fp), (len-1)*sizeof(struct Sportsmen));
    fclose(fp);
}

// Вместо спортсмена на index позиции ставиться sportsmen
// Нумерация с нуля
void updateSportsmen(int index, struct Sportsmen sportsmen) {
    FILE *fp;
    fp = fopen(FILE_NAME, "r+");

    fseek(fp, index*sizeof(struct Sportsmen), SEEK_SET);
    fwrite(&sportsmen, sizeof(struct Sportsmen), 1, fp);

    fclose(fp);
}

// Вывод содержимого файла в консоль
void printFile() {
    FILE *fp;
    fp = fopen(FILE_NAME, "r");
    struct Sportsmen s;

    while (!feof(fp)) {
        if (fread(&s, sizeof(s), 1, fp) > 0) {
            printSportsmen(s);
        }
    }
    printf("\n");
    fclose(fp);
}

// Найти самых высоких спортсменов
int getMaxHeight() {
    FILE *fp;
    fp = fopen(FILE_NAME, "r");
    struct Sportsmen s;
    int maxHeight = 0;

    while (!feof(fp)) {
        if (fread(&s, sizeof(s), 1, fp) > 0) {
            if (maxHeight <= s.height) {
                maxHeight = s.height;
            }
        }
    }
    return maxHeight;
}
