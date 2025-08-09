#include "format/cpp/format_cpp.h"
#include <string.h>

bool cppIsFormatNameRaw(char *formatName) {
        return strcmp("cpp-raw", formatName) == 0;
}

#define CPP_VALUES_PER_LINE 16

// TODO Open context in raw mode
void cppBakeRaw(BakeContext *context, char *headerDefName, char *namespaceName, char *varName,
    char *lenVarName) {
    // #ifndef [...]
    contextWriteStr(context, "#ifndef ") &&
    contextWriteStr(context, headerDefName) &&
    contextWriteStr(context, "\n") &&

    // #define [...]
    contextWriteStr(context, "#define ") &&
    contextWriteStr(context, headerDefName) &&
    contextWriteStr(context, "\n\n") &&
    
    // namespace [...]  {
    contextWriteStr(context, "namespace ") &&
    contextWriteStr(context, namespaceName) &&
    contextWriteStr(context, " {\n\n") &&

    // const char [...][] = {    "   
    contextWriteStr(context, "    const char ") &&
    contextWriteStr(context, varName) &&
    contextWriteStr(context, "[] = {\n        ");

    // [...],
    bool firstValue = true;
    int valuesInLine = 0;
    int valuesCount = 0;
    char content;
    while ((content = contextReadChar(context)) != EOF) {
        if (!firstValue)
            contextWriteStr(context, ", ");
        else
            firstValue = false;
                
        if (valuesInLine >= CPP_VALUES_PER_LINE) {
            contextWriteStr(context, "\n        ");
            valuesInLine = 0;
        }

        contextWriteStr(context, "0x");
        contextWriteHexValue(context, content);
        valuesInLine++;
        valuesCount++;
    }

    // };    const int
    contextWriteStr(context, "};\n\n    const int ");

    // [...] = [...];
    contextWriteStr(context, lenVarName);
    contextWriteStr(context, " = ");
    contextWriteInt(context, valuesCount);
    contextWriteStr(context, ";\n\n");
    

    // } #endif
    contextWriteStr(context, "}\n\n#endif\n");
}
