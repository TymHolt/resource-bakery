#include "bake_context.h"
#include <stdlib.h>
#include <string.h>

bool tryContextOpen(char *srcFile, char *dstFile, BakeContext *result) {
    FILE *srcHandle;
    FILE *dstHandle;

    if ((srcHandle = fopen(srcFile, "r")) == NULL) {
        printf("Source file '%s' could not be opened\n", srcFile);
        return false;
    }

    if ((dstHandle = fopen(dstFile, "w")) == NULL) {
        printf("Destination file '%s' could not be opened\n", dstFile);
        fclose(srcHandle);
        return false;
    }

    result->srcHandle = srcHandle;
    result->dstHandle = dstHandle;
    result->errorCount = 0;
    return true;
}

void contextClose(BakeContext *context) {
    fclose(context->srcHandle);
    fclose(context->dstHandle);
}

bool contextHadErrors(BakeContext *context) {
    return context->errorCount > 0;
}

char contextReadChar(BakeContext *context) {
    return fgetc(context->srcHandle);
}

bool contextWriteStr(BakeContext *context, char *content) {
    if (fprintf(context->dstHandle, "%s", content) != strlen(content)) {
        context->errorCount++;
        return false;
    }

    return true;
}

bool contextWriteChar(BakeContext *context, char content) {
    if (((char) fputc(content, context->dstHandle)) != content) {
        context->errorCount++;
        return false;
    }

    return true;
}