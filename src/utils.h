#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

bool charIsAlphaNum(char c);
void strAlphaNum(char *str, char replace);
char *strCpyAlphaAlloc(char *src);
char *strConcatAlloc(char *left, char *right);
char *strFileNameNoExtAlphaAlloc(char *fileName);
char getHexDigit(int value);

#endif