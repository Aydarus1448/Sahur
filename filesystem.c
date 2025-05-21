#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filesystem.h"

FILE* sahur_open(const char* filename) {
    FILE* fs = fopen(filename, "a+");
    if (!fs) {
        perror("Sahur: Failed to open filesystem");
        return NULL;
    }
    return fs;
}

char* sahur_view(FILE* fs, const char* filename) {
    fseek(fs, 0, SEEK_SET);
    char line[256];
    int found = 0;
    char* content = NULL;
    size_t content_size = 0;
    
    while (fgets(line, sizeof(line), fs)) {
        line[strcspn(line, "\n")] = 0;
        
        if (!found) {
            if (strcmp(line, filename) == 0) {
                found = 1;
            }
        } else {
            if (line[0] == '/') {
                break;
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

int sahur_delete(FILE* fs, const char* filename) {
    fseek(fs, 0, SEEK_SET);
    char** lines = NULL;
    int line_count = 0;
    int in_target_file = 0;
    char line[256];
    
    while (fgets(line, sizeof(line), fs) {
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

int sahur_create(FILE* fs, const char* filename, const char* content) {
    fseek(fs, 0, SEEK_END);
    
    fseek(fs, 0, SEEK_SET);
    char line[256];
    while (fgets(line, sizeof(line), fs) {
        line[strcspn(line, "\n")] = 0;
        if (strcmp(line, filename) == 0) {
            return 0;
        }
    }
    
    fprintf(fs, "%s\n", filename);
    fprintf(fs, "%s\n", content);
    fprintf(fs, "/\n");
    
    return 1;
}

int sahur_modify(FILE* fs, const char* filename, const char* new_content) {
    if (!sahur_delete(fs, filename)) {
        return 0;
    }
    
    fseek(fs, 0, SEEK_END);
    fprintf(fs, "%s\n", filename);
    fprintf(fs, "%s\n", new_content);
    fprintf(fs, "/\n");
    
    return 1;
}
