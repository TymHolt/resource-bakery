#include <format/cpp/format_cpp.h>
#include <stdbool.h>
#include <string.h>

bool cppIsFormatName(char *formatName) {
    return strcmp("cpp-text", formatName) == 0
        || strcmp("c++-text", formatName) == 0; 
}

bool writeCharCheckEscape(BakeContext *context, char content) {
    switch (content) {
        case '\"':
            return contextWriteStr(context, "\\\"");
        case '\r':
            return contextWriteStr(context, "\\r");
        case '\t':
            return contextWriteStr(context, "\\t");            
        default:
            return contextWriteChar(context, content);
    }
}

bool cppBakeText(BakeContext *context, char *headerDefName, char *namespaceName, char *varName) {
    bool success =
        // #define [...]
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
            success = contextWriteStr(context, "\\n\"\n        \"") && success;    
        else
            success = writeCharCheckEscape(context, content);
    }

    // "; } #endif
    success = contextWriteStr(context, "\";\n\n}\n\n#endif\n") && success;
    return success;
}