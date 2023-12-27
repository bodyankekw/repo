#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

void write_to_file(char *filename) {
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        printf("Ошибка при открытии файла!\n");
        return;
    }

    char data[MAX_SIZE];
    printf("Введите данные для записи в файл (для завершения нажмите Ctrl+D):\n");

    while (fgets(data, MAX_SIZE, stdin) != NULL) {
        fprintf(file, "%s", data);
    }

    fclose(file);
    printf("Данные успешно записаны в файл %s\n", filename);
}

void read_from_file(char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Ошибка при открытии файла!\n");
        return;
    }

    char data[MAX_SIZE];
    printf("Содержимое файла %s:\n", filename);

    while (fgets(data, MAX_SIZE, file) != NULL) {
        printf("%s", data);
    }

    fclose(file);
}


int main(int argc, char *argv[])
{
    if (argc > 3)
    {
        fprintf(stderr, "Usage: mycat <filename> or mycat > <filename>\n");
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1],">") == 0)
    {
        write_to_file(argv[2]);
    }
    else
    {
        read_from_file(argv[1]);
    }

    return 0;
}