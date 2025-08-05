#include "utils.h"

#include <stdlib.h>
#include <string.h>

bool charIsAlphaNum(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_';
}

// Override a given string to be alpha numeric
void strAlphaNum(char *str, char replace) {
    size_t idx = 0;
    char c;

    while ((c = str[idx]) != '\0') {
        if (!charIsAlphaNum(c))
            str[idx] = replace;
        
        idx++;    
    }
}

// Copy the string as new allocation and make alpha numeric
char *strCpyAlphaAlloc(char *src) {
    char *dst = (char *) malloc(sizeof(char) * (strlen(src) + 1));
    strcpy(dst, src);
    strAlphaNum(dst, '_');

    return dst;
}

// Concat the given string and return as new allocation
char *strConcatAlloc(char *left, char *right) {
    char *res = (char *) malloc(sizeof(char) * (strlen(left) + strlen(right) + 1));
    strcpy(res, left);
    strcat(res, right);
    
    return res;
}