#ifndef FORMAT_CPP_H
#define FORMAT_CPP_H

#include <stdbool.h>
#include "bake_context.h"

bool cppIsFormatName(char *formatName);
bool cppBakeText(BakeContext *context, char *headerDefName, char *namespaceName, char *varName);

#endif