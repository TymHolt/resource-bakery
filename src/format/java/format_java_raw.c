#include "format/java/format_java.h"
#include <string.h>

bool javaIsFormatNameRaw(char *formatName) {
    return strcmp("java-raw", formatName) == 0;
}

#define JAVA_VALUES_PER_LINE 16

// TODO Open context in raw mode
void javaBakeRaw(BakeContext *context, char *packageName, char *className, char *varName) {
    // package [...]
    contextWriteStr(context, "package ") &&
    contextWriteStr(context, packageName) &&
    contextWriteStr(context, ";\n\n") &&

    // public class [...] {
    contextWriteStr(context, "public class ") &&
    contextWriteStr(context, className) &&
    contextWriteStr(context, " {\n\n") &&

    
    // public static final byte[] [...] = new byte[] {
    contextWriteStr(context, "    public static final byte[] ") &&
    contextWriteStr(context, varName) &&
    contextWriteStr(context, " = new byte[] {\n        ");

    // (byte) [...],
    bool firstValue = true;
    int valuesInLine = 0;
    char content;
    while ((content = contextReadChar(context)) != EOF) {
        if (!firstValue)
            contextWriteStr(context, ", ");
        else
            firstValue = false;
                
        if (valuesInLine >= JAVA_VALUES_PER_LINE) {
            contextWriteStr(context, "\n        ");
            valuesInLine = 0;
        }

        contextWriteStr(context, "(byte) 0x");
        contextWriteHexValue(context, content);
        valuesInLine++;
    }

    // "; }
    contextWriteStr(context, "};\n}\n");
}