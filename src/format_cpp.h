#ifndef FORMAT_CPP_H
#define FORMAT_CPP_H

#include <stdbool.h>
#include "bake_context.h"

bool cppIsFormatName(char *formatName);
bool cppBake(BakeContext *context, char *dstFile);

#endif