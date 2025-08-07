#include "format/cpp/format_cpp.h"
#include <string.h>

bool cppIsFormatNameText(char *formatName) {
    return strcmp("cpp-text", formatName) == 0
        || strcmp("c++-text", formatName) == 0; 
}

void cppWriteCharCheckEscape(BakeContext *context, char content) {
    switch (content) {
        case '\"':
            contextWriteStr(context, "\\\"");
            break;
        case '\r':
            contextWriteStr(context, "\\r");
            break;
        case '\t':
            contextWriteStr(context, "\\t");
            break;            
        default:
            contextWriteChar(context, content);
            break;
    }
}

void cppBakeText(BakeContext *context, char *headerDefName, char *namespaceName, char *varName) {
    // #ifndef [...]
    contextWriteStr(context, "#ifndef ") &&
    contextWriteStr(context, headerDefName) &&
    contextWriteStr(context, "\n") &&

    // #define [...]
    contextWriteStr(context, "#define ") &&
    contextWriteStr(context, headerDefName) &&
    contextWriteStr(context, "\n\n") &&

    // #include <string>
    contextWriteStr(context, "#include <string>\n\n") &&
    
    // namespace [...]  {
    contextWriteStr(context, "namespace ") &&
    contextWriteStr(context, namespaceName) &&
    contextWriteStr(context, " {\n\n") &&

    // const std::string [...] =    "
    contextWriteStr(context, "    const std::string ") &&
    contextWriteStr(context, varName) &&
    contextWriteStr(context, " =\n        \"");

    // ...\n"   "...
    char content;
    while ((content = contextReadChar(context)) != EOF) {
        if (content == '\n')
            contextWriteStr(context, "\\n\"\n        \"");    
        else
            cppWriteCharCheckEscape(context, content);
    }

    // "; } #endif
    contextWriteStr(context, "\";\n\n}\n\n#endif\n");
}