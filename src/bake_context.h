#ifndef BAKE_CONTEXT_H
#define BAKE_CONTEXT_H

#include <stdio.h>
#include <stdbool.h>

typedef struct BakeContext_Struct {
    FILE *srcHandle;
    FILE *dstHandle;
    char *contentBuffer;
} BakeContext;

bool tryContextOpen(char *srcFile, char *dstFile, BakeContext *result);
void contextClose(BakeContext *context);
bool contextEndOfSrc(BakeContext *context);
bool tryContextRead(BakeContext *context);

#endif