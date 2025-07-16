#include "bake_context.h"
#include <stdlib.h>

#define CONTENT_BUFFER_SIZE 1024

bool tryContextOpen(char *srcFile, char *dstFile, BakeContext *result) {
    FILE *srcHandle;
    FILE *dstHandle;
    char *contentBuffer;

    if ((srcHandle = fopen(srcFile, "r")) == NULL) {
        printf("Source file '%s' could not be opened\n", srcFile);
        return false;
    }

    if ((dstHandle = fopen(dstFile, "w")) == NULL) {
        printf("Destination file '%s' could not be opened\n", dstFile);
        fclose(srcHandle);
        return false;
    }

    if ((contentBuffer = (char *) malloc(CONTENT_BUFFER_SIZE * sizeof(char))) == NULL) {
        printf("Content buffer could not be allocated\n");
        fclose(srcHandle);
        fclose(dstHandle);
        return false;
    }

    result->srcHandle = srcHandle;
    result->dstHandle = dstHandle;
    result->contentBuffer = contentBuffer;
    return true;
}

void contextClose(BakeContext *context) {
    fclose(context->srcHandle);
    fclose(context->dstHandle);
    free(context->contentBuffer);
}

bool contextEndOfSrc(BakeContext *context) {
    return feof(context->srcHandle);
}

bool tryContextRead(BakeContext *context) {
    return fgets(context->contentBuffer, CONTENT_BUFFER_SIZE, context->srcHandle) ==
        context->contentBuffer;
}