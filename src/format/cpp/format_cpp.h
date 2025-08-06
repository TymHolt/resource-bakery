#ifndef FORMAT_CPP_H
#define FORMAT_CPP_H

#include <stdbool.h>
#include "bake_context.h"

bool cppIsFormatNameText(char *formatName);
void cppBakeText(BakeContext *context, char *headerDefName, char *namespaceName, char *varName);

#endif