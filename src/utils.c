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

// Return the given file name wihtout its extension as a new allocation
char *strFileNameNoExtAlphaAlloc(char *fileName) {
    const size_t no_ext = -1;
    size_t extIdx = no_ext;
    size_t idx = 0;
    char c;

    while((c = fileName[idx]) != '\0') {
        if (c == '.')
            extIdx = idx;

        idx++;
    }

    // Default value. If no extension is found, return whole file name
    size_t newLen = idx + 1;

    if (extIdx != no_ext) {
        // Extension found, calculate new length
        newLen = extIdx; // No +1, so the '.' won't be included
    }

    char *res = (char *) malloc(sizeof(char) * (newLen + 1));
    strncpy(res, fileName, newLen);
    res[newLen] = '\0';

    strAlphaNum(res, '_');

    return res;
}