#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* open_fs(const char* filename) {
    FILE* fs = fopen(filename, "a+"); // Открываем для чтения и записи
    if (!fs) {
        perror("Failed to open filesystem");
        return NULL;
    }
    return fs;
}

char* view_file(FILE* fs, const char* filename) {
    fseek(fs, 0, SEEK_SET);
    char line[256];
    int found = 0;
    char* content = NULL;
    size_t content_size = 0;
    
    while (fgets(line, sizeof(line), fs)) {
        line[strcspn(line, "\n")] = 0; // Удаляем символ новой строки
        
        if (!found) {
            if (strcmp(line, filename) == 0) {
                found = 1;
            }
        } else {
            if (line[0] == '/') {
                break; // Конец файла
            }
            
            size_t line_len = strlen(line);
            char* temp = realloc(content, content_size + line_len + 2);
            if (!temp) {
                free(content);
                return NULL;
            }
            content = temp;
            strcpy(content + content_size, line);
            content_size += line_len;
            strcpy(content + content_size, "\n");
            content_size += 1;
        }
    }
    
    return content;
}

int delete_file(FILE* fs, const char* filename) {
    fseek(fs, 0, SEEK_SET);
    char** lines = NULL;
    int line_count = 0;
    int in_target_file = 0;
    char line[256];
    
    while (fgets(line, sizeof(line), fs)) {
        line[strcspn(line, "\n")] = 0;
        
        if (!in_target_file) {
            if (strcmp(line, filename) == 0) {
                in_target_file = 1;
                continue;
            }
        } else {
            if (line[0] == '/') {
                in_target_file = 0;
            } else {
                continue;
            }
        }
        
        char** temp = realloc(lines, (line_count + 1) * sizeof(char*));
        if (!temp) {
            for (int i = 0; i < line_count; i++) free(lines[i]);
            free(lines);
            return 0;
        }
        lines = temp;
        lines[line_count] = strdup(line);
        line_count++;
    }
    
    freopen(NULL, "w", fs);
    for (int i = 0; i < line_count; i++) {
        fprintf(fs, "%s\n", lines[i]);
        free(lines[i]);
    }
    free(lines);
    
    return 1;
}
