#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filesystem.h"

int main() {
    FILE* fs = sahur_open("sahur.disk");
    if (!fs) return 1;

    char command[256];
    char* args[3];
    
    while (1) {
        printf("> ");
        if (!fgets(command, sizeof(command), stdin)) break;
        
        command[strcspn(command, "\n")] = 0;
        args[0] = strtok(command, " ");
        args[1] = strtok(NULL, " ");
        args[2] = strtok(NULL, "");
        
        if (!args[0]) continue;
        
        if (strcmp(args[0], "create") == 0 && args[1] && args[2]) {
            sahur_create(fs, args[1], args[2]);
        } 
        else if (strcmp(args[0], "delete") == 0 && args[1]) {
            sahur_delete(fs, args[1]);
        }
        else if (strcmp(args[0], "modify") == 0 && args[1] && args[2]) {
            sahur_modify(fs, args[1], args[2]);
        }
        else if (strcmp(args[0], "view") == 0 && args[1]) {
            char* content = sahur_view(fs, args[1]);
            if (content) {
                printf("%s\n", content);
                free(content);
            }
        }
        else if (strcmp(args[0], "exit") == 0) {
            break;
        }
    }
    
    fclose(fs);
    return 0;
}
