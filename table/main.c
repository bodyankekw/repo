#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 50
#define MAX_RECORDS 100


typedef struct {
    char surname[MAX_LEN];
    int student_id;
    char faculty[MAX_LEN];
    int group;
} StudentRecord;


StudentRecord table[MAX_RECORDS];
int num_records = 0;


void input_record() {
    if (num_records >= MAX_RECORDS) {
        printf("Таблица заполнена.\n");
        return;
    }

    StudentRecord newRecord;

    printf("Введите фамилию: ");
    scanf("%s", newRecord.surname);
    printf("Введите номер зачетной книжки: ");
    scanf("%d", &newRecord.student_id);
    printf("Введите факультет: ");
    scanf("%s", newRecord.faculty);
    printf("Введите номер группы: ");
    scanf("%d", &newRecord.group);

    table[num_records++] = newRecord;
    printf("Запись добавлена в таблицу.\n");
}

void display_table() {
    if (num_records == 0) {
        printf("Таблица пуста.\n");
        return;
    }

    printf("Таблица записей студентов:\n");
    printf("Фамилия\t\tНомер зачетной книжки\tФакультет\tГруппа\n");
    for (int i = 0; i < num_records; ++i) {
        printf("%s\t\t%d\t\t%s\t\t%d\n",
               table[i].surname, table[i].student_id,
               table[i].faculty, table[i].group);
    }
}

void save_to_file() {
    FILE *fp;
    fp = fopen("students.txt", "w");

    if (fp == NULL) {
        printf("Ошибка открытия файла.\n");
        return;
    }

    for (int i = 0; i < num_records; ++i) {
        fprintf(fp, "%s %d %s %d\n",
                table[i].surname, table[i].student_id,
                table[i].faculty, table[i].group);
    }

    fclose(fp);
    printf("Таблица сохранена в файле 'students.txt'.\n");
}

void load_from_file() {
    FILE *fp;
    fp = fopen("students.txt", "r");

    if (fp == NULL) {
        printf("Ошибка открытия файла.\n");
        return;
    }

    num_records = 0;
    while (fscanf(fp, "%s %d %s %d",
                  table[num_records].surname, &table[num_records].student_id,
                  table[num_records].faculty, &table[num_records].group) != EOF) {
        num_records++;
    }

    fclose(fp);
    printf("Таблица загружена из файла 'students.txt'.\n");
}

void sort_table(int field) {
    for (int i = 0; i < num_records - 1; ++i) {
        for (int j = 0; j < num_records - i - 1; ++j) {
            if (field == 2 && table[j].student_id > table[j + 1].student_id) {
                StudentRecord temp = table[j];
                table[j] = table[j + 1];
                table[j + 1] = temp;
            } else if (field == 4 && table[j].group > table[j + 1].group) {
                StudentRecord temp = table[j];
                table[j] = table[j + 1];
                table[j + 1] = temp;
            }
        }
    }
    printf("Таблица отсортирована.\n");
}

void search_record(int field, int value) {
    int found = 0;

    for (int i = 0; i < num_records; ++i) {
        if ((field == 2 && table[i].student_id == value) ||
            (field == 4 && table[i].group == value)) {
            printf("Найден элемент: %s %d %s %d\n",
                   table[i].surname, table[i].student_id,
                   table[i].faculty, table[i].group);
            found = 1;
        }
    }

    if (!found) {
        printf("Элемент не найден.\n");
    }
}

void delete_record(int index) {
    if (index < 0 || index >= num_records) {
        printf("Некорректный индекс.\n");
        return;
    }

    for (int i = index; i < num_records - 1; ++i) {
        table[i] = table[i + 1];
    }

    num_records--;
    printf("Запись удалена.\n");
}

void edit_record(int index) {
    if (index < 0 || index >= num_records) {
        printf("Некорректный индекс.\n");
        return;
    }

    printf("Введите новую фамилию: ");
    scanf("%s", table[index].surname);
    printf("Введите новый номер зачетной книжки: ");
    scanf("%d", &table[index].student_id);
    printf("Введите новый факультет: ");
    scanf("%s", table[index].faculty);
    printf("Введите новый номер группы: ");
    scanf("%d", &table[index].group);

    printf("Запись изменена.\n");
}

void count_by_group(int group) {
    int count = 0;

    for (int i = 0; i < num_records; ++i) {
        if (table[i].group == group) {
            count++;
        }
    }

    printf("Всего студентов в группе %d: %d\n", group, count);
}

int main() {
    int choice;

    StudentRecord record;
    record.group = 123;
    record.student_id = 12345;
    strcpy(record.faculty, "АВТФ");
    strcpy(record.surname, "Волков");
    table[num_records++] = record;

    record.group = 122;
    record.student_id = 12346;
    strcpy(record.faculty, "АВТФ");
    strcpy(record.surname, "Богданов");
    table[num_records++] = record;

    do {
        printf("\nМеню:\n");
        printf("1. Ввод записи\n");
        printf("2. Просмотр таблицы\n");
        printf("3. Сохранить таблицу в файл\n");
        printf("4. Загрузить таблицу из файла\n");
        printf("5. Сортировать таблицу\n");
        printf("6. Поиск элемента\n");
        printf("7. Удаление записи\n");
        printf("8. Редактирование записи\n");
        printf("9. Вычисление по группе\n");
        printf("0. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                input_record();
                break;
            case 2:
                display_table();
                break;
            case 3:
                save_to_file();
                break;
            case 4:
                load_from_file();
                break;
            case 5:
                printf("Выберите поле для сортировки:\n");
                printf("2. Номер зачетной книжки\n");
                printf("4. Группа\n");
                printf("Введите номер поля: ");
                int field;
                scanf("%d", &field);
                sort_table(field);
                break;
            case 6:
                printf("Выберите поле для поиска:\n");
                printf("2. Номер зачетной книжки\n");
                printf("4. Группа\n");
                printf("Введите номер поля: ");
                int searchField, searchValue;
                scanf("%d", &searchField);
                printf("Введите значение для поиска: ");
                scanf("%d", &searchValue);
                search_record(searchField, searchValue);
                break;
            case 7:
                printf("Введите индекс записи для удаления: ");
                int deleteIndex;
                scanf("%d", &deleteIndex);
                delete_record(deleteIndex);
                break;
            case 8:
                printf("Введите индекс записи для редактирования: ");
                int editIndex;
                scanf("%d", &editIndex);
                edit_record(editIndex);
                break;
            case 9:
                printf("Введите номер группы для вычисления: ");
                int group;
                scanf("%d", &group);
                count_by_group(group);
                break;
            case 0:
                printf("Программа завершена.\n");
                break;
            default:
                printf("Некорректный ввод. Попробуйте снова.\n");
        }
    } while (choice != 0);

    return 0;
}
