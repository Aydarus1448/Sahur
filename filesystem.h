#ifndef SAHUR_FILESYSTEM_H
#define SAHUR_FILESYSTEM_H

#include <stdio.h>

FILE* sahur_open(const char* filename);
char* sahur_view(FILE* fs, const char* filename);
int sahur_delete(FILE* fs, const char* filename);
int sahur_create(FILE* fs, const char* filename, const char* content);
int sahur_modify(FILE* fs, const char* filename, const char* new_content);

#endif // SAHUR_FILESYSTEM_H
