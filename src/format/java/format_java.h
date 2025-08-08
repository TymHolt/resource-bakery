#ifndef FORMAT_JAVA_H
#define FORMAT_JAVA_H

#include <stdbool.h>
#include "bake_context.h"

bool javaIsFormatNameText(char *formatName);
void javaBakeText(BakeContext *context, char *packageName, char *className, char *varName);
bool javaIsFormatNameRaw(char *formatName);
void javaBakeRaw(BakeContext *context, char *packageName, char *className, char *varName);


#endif