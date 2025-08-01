#include <format/cpp/format_cpp.h>
#include <stdbool.h>
#include <string.h>

bool cppIsFormatName(char *formatName) {
    return strcmp("cpp", formatName) == 0
        || strcmp("c++", formatName) == 0; 
}

bool printStr(FILE *dstHandle, char *str) {
    return fprintf(dstHandle, "%s", str) == strlen(str);
}

bool printC(FILE *dstHandle, char c) {
    return fputc(c, dstHandle) == c;
}

bool printNl(FILE *dstHandle) {
    return printC(dstHandle, '\n');
}

bool isAlphaNum(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_';
}

void *makeAlphaNum(char *str) {
    size_t len = strlen(str);
    for (size_t idx = 0; idx < len; idx++) {
        if (!isAlphaNum(str[idx]))
            str[idx] = '_';
    }
}

#define IDENT_MAX_LENGTH 255
#define DEF_SUFFIX "_H"

bool printHeadSection(FILE* dstHandle, char *dstFile) {
    // Namespace identifier (namespace [...])
    char ident[IDENT_MAX_LENGTH - sizeof(DEF_SUFFIX) + 2]; // sizeof(DEF_SUFFIX) includes \0 -> + 2

    size_t identStrLen = strlen(dstFile);
    size_t identStrLenMax = sizeof(ident) - 1;
    if (identStrLen > identStrLenMax)
        identStrLen = identStrLenMax;

    strncpy(ident, dstFile, identStrLen);
    ident[identStrLen] = '\0';
    makeAlphaNum(ident);

    // Header define identifier (#define [...])
    char defIdent[IDENT_MAX_LENGTH + 1];
    strcpy(defIdent, ident);
    strcpy(defIdent + identStrLen, DEF_SUFFIX);
    defIdent[sizeof(defIdent) - 1] = '\0';

    return fprintf(dstHandle, "#ifndef %s\n#define %s\n\n#include <string>\n\nnamespace %s {\n\n",
        defIdent, defIdent, ident) > 0
        && fprintf(dstHandle, "    const std::string content =");
}

bool printContentStartLn(FILE *dstHandle) {
    return fprintf(dstHandle, "\n        \"");
}

bool printContentEndLn(FILE *dstHandle) {
    return fprintf(dstHandle, "\\n\"");
}


bool printTailSection(FILE* dstHandle) {
    return fprintf(dstHandle, ";\n}\n\n#endif\n");
}

bool cppBake(BakeContext *context, char *dstFile) {
    printHeadSection(context->dstHandle, dstFile);
    printContentStartLn(context->dstHandle);

    char c;
    while ((c = fgetc(context->srcHandle)) != EOF) {
        bool success = false;

        if (c == '\n')
            success = printContentEndLn(context->dstHandle) && printContentStartLn(context->dstHandle);
        else
            success = ((char) fputc(c, context->dstHandle)) == c;

        if (!success)
            return success;
    }

    printContentEndLn(context->dstHandle);
    printTailSection(context->dstHandle);
    return true;
}