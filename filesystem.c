#include <stdio.h>
#include <string.h>

FILE* open_fs_file(char* path) {
    FILE* file = fopen(path, "r+");
    
    if (file == NULL) {
        file = fopen(path, "w+");
        printf("Создали новый файл %s\n", path);
    } else {
        printf("Открыли существующий файл %s\n", path);
    }
    
    if (file == NULL) {
        printf("Ошибка! Не могу открыть файл!\n");
    }
    
    return file;
}

void view_file(FILE* fs, char* filename) {
    char line[100]; // Буфер для чтения строк
    int found = 0;  // Флаг "нашли ли файл"
    

    rewind(fs);
    
    while (fgets(line, sizeof(line), fs)) {

        line[strlen(line)-1] = '\0';
      
        if (strcmp(line, filename) == 0) {
            found = 1;
            printf("Содержимое файла %s:\n", filename);
            continue;
        }
        

        if (line[0] == '/') {
            found = 0;
        }
        
        if (found) {
            printf("%s\n", line);
        }
    }
    
    if (!found) {
        printf("Файл %s не найден!\n", filename);
    }
}

void delete_file(FILE* fs, char* filename) {
    char line[100];
    int copying = 1;
    FILE* temp;
    
    temp = fopen("temp.fs", "w");
    if (temp == NULL) {
        printf("Ошибка создания временного файла!\n");
        return;
    }
    
    rewind(fs);
    
    while (fgets(line, sizeof(line), fs)) {
        line[strlen(line)-1] = '\0';
        

        if (strcmp(line, filename) == 0) {
            copying = 0; 
            continue;
        }
        
        if (line[0] == '/') {
            copying = 1; 
        }
        
        if (copying) {
            fprintf(temp, "%s\n", line);
        }
    }
    
    fclose(temp);
    fclose(fs);
    
    remove("data.fs");
    rename("temp.fs", "data.fs");
    
    printf("Файл %s удалён!\n", filename);
}
