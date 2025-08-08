#ifndef BAKE_CONTEXT_H
#define BAKE_CONTEXT_H

#include <stdio.h>
#include <stdbool.h>

typedef struct BakeContext_Struct {
    FILE *srcHandle;
    FILE *dstHandle;
    bool *errorCount;
} BakeContext;

bool tryContextOpen(char *srcFile, char *dstFile, BakeContext *result);
void contextClose(BakeContext *context);
bool contextHadErrors(BakeContext *context);
char contextReadChar(BakeContext *context);
bool contextWriteStr(BakeContext *context, char *content);
bool contextWriteChar(BakeContext *context, char content);
bool contextWriteHexValue(BakeContext *context, char value);

#endif