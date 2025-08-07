#include "format/java/format_java.h"
#include <string.h>

bool javaIsFormatNameText(char *formatName) {
    return strcmp("java-text", formatName) == 0;
}

void javaWriteCharCheckEscape(BakeContext *context, char content) {
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

void javaBakeText(BakeContext *context, char *packageName, char *className, char *varName) {
    // package [...]
    contextWriteStr(context, "package ") &&
    contextWriteStr(context, packageName) &&
    contextWriteStr(context, ";\n\n") &&

    // public class [...] {
    contextWriteStr(context, "public class ") &&
    contextWriteStr(context, className) &&
    contextWriteStr(context, " {\n\n") &&

    // public static final String [...] =    "
    contextWriteStr(context, "    public static final String ") &&
    contextWriteStr(context, varName) &&
    contextWriteStr(context, " =\n        \"");

    // ...\n" +   "...
    char content;
    while ((content = contextReadChar(context)) != EOF) {
        if (content == '\n')
            contextWriteStr(context, "\\n\" +\n        \"");    
        else
            javaWriteCharCheckEscape(context, content);
    }

    // "; } #endif
    contextWriteStr(context, "\";\n}\n");
}