#include <format/cpp/format_cpp.h>
#include <stdbool.h>
#include <string.h>

bool cppIsFormatName(char *formatName) {
    return strcmp("cpp-text", formatName) == 0
        || strcmp("c++-text", formatName) == 0; 
}

bool cppBakeText(BakeContext *context, char *headerDefName, char *namespaceName, char *varName) {
    bool success =
        // #define [...]
        tryContextWriteStr(context, "#ifndef ") &&
        tryContextWriteStr(context, headerDefName) &&
        tryContextWriteStr(context, "\n") &&

        // #define [...]
        tryContextWriteStr(context, "#define ") &&
        tryContextWriteStr(context, headerDefName) &&
        tryContextWriteStr(context, "\n\n") &&
    
        // #include <string>
        tryContextWriteStr(context, "#include <string>\n\n") &&
        
        // namespace [...]  {
        tryContextWriteStr(context, "namespace ") &&
        tryContextWriteStr(context, namespaceName) &&
        tryContextWriteStr(context, " {\n\n") &&

        // const std::string [...] =    "
        tryContextWriteStr(context, "    const std::string ") &&
        tryContextWriteStr(context, varName) &&
        tryContextWriteStr(context, " =\n        \"");

    // ...\n"   "...
    char content;
    while ((content = contextReadChar(context)) != EOF) {
        if (content == '\n')
            success = tryContextWriteStr(context, "\\n\"\n        \"") && success;    
        else
            success = tryContextWriteChar(context, content);
    }

    // "; } #endif
    success = tryContextWriteStr(context, "\";\n\n}\n\n#endif\n") && success;
    return success;
}