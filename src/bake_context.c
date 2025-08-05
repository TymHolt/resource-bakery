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
    return true;
}

void contextClose(BakeContext *context) {
    fclose(context->srcHandle);
    fclose(context->dstHandle);
}

char contextReadChar(BakeContext *context) {
    return fgetc(context->srcHandle);
}

bool tryContextWriteStr(BakeContext *context, char *content) {
    return fprintf(context->dstHandle, "%s", content) == strlen(content);
}

bool tryContextWriteChar(BakeContext *context, char content) {
    return ((char) fputc(content, context->dstHandle)) == content;
}