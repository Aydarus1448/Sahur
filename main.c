#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filesystem.h"

int main() {
    FILE* fs = sahur_open("sahur.disk");
    if (!fs) return 1;
    
    sahur_create(fs, "test.txt", "Hello Sahur!");
    char* content = sahur_view(fs, "test.txt");
    if (content) {
        printf("Content: %s\n", content);
        free(content);
    }
    
    fclose(fs);
    return 0;
}
