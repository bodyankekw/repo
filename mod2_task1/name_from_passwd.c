#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 666
#define MAX_FIELDS 7

int main() {
    char login[50] = {0};
    printf("Введите логин пользователя: ");
    scanf("%s", login);

    FILE *file = fopen("/etc/passwd", "r");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        return EXIT_FAILURE;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        char *token;
        token = strtok(line, ":");

        int count = 0;
        char *fields[MAX_FIELDS];

        while (token != NULL && count < MAX_FIELDS) {
            fields[count] = token;
            count++;
            token = strtok(NULL, ":");
        }

        if (count >= 5 && strcmp(fields[0], login) == 0) {
            if (strlen(fields[4]) > 0) {
                char *subtoken = strtok(fields[4], ",");
                if (subtoken != NULL) {
                    printf("Имя %s: %s\n", login, subtoken);
                    fclose(file);
                    return 0;
                }
            }
        }
    }

    printf("Пользователь с логином '%s' не найден или отсутствует имя\n", login);
    fclose(file);
    return 1;
}