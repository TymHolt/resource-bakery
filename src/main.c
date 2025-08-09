#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "format/cpp/format_cpp.h"
#include "format/java/format_java.h"

typedef struct Args_Struct {
    int argc;    // Arguments count
    char **argv; // Arguments values
    int argi;    // Arguments current index
} Args;

bool argsHasMore(Args *args) {
    return args->argi < args->argc;
}

bool tryArgsGetNext(Args *args, char **result) {
    if (argsHasMore(args)) {
        *result = args->argv[args->argi++];
        return true;
    }

    return false;
}

void printUsage(char *execName) {
    printf("Usage: %s [format] [src] [dst]\n", execName);
}

#define EXIT_SUCCESS 0
#define EXIT_ERROR -1

int main(int argc, char **argv) {
    Args args;
    args.argc = argc;
    args.argv = argv;
    args.argi = 0;

    char *execName;
    if (!tryArgsGetNext(&args, &execName)) {
        printf("No executable name given\n");
        printUsage("bake");
        return EXIT_ERROR;
    }

    char *bakeFormat;
    if (!tryArgsGetNext(&args, &bakeFormat)) {
        printf("No bake format given\n");
        printUsage(execName);
        return EXIT_ERROR;
    }

    char *srcFileName;
    if (!tryArgsGetNext(&args, &srcFileName)) {
        printf("No source file given\n");
        printUsage(execName);
        return EXIT_ERROR;
    }

    char *dstFileName;
    if (!tryArgsGetNext(&args, &dstFileName)) {
        printf("No destination file given\n");
        printUsage(execName);
        return EXIT_ERROR;
    }

    if (argsHasMore(&args)) {
        printf("Too many arguments\n");
        printUsage(execName);
        return EXIT_ERROR;
    }

    BakeContext context;
    if (!tryContextOpen(srcFileName, dstFileName, &context)) {
        printf("Could not create baking context\n");
        return EXIT_ERROR;
    }

    int exitCode = EXIT_SUCCESS;

    if (cppIsFormatNameText(bakeFormat)) {
        char *namespaceName = strCpyAlphaAlloc(dstFileName);
        char *headerDefName = strConcatAlloc(namespaceName, "_H");
        char *varName = "content";

        cppBakeText(&context, namespaceName, headerDefName, varName);

        free(headerDefName);
        free(namespaceName);
    } else if (cppIsFormatNameRaw(bakeFormat)) {
        char *namespaceName = strCpyAlphaAlloc(dstFileName);
        char *headerDefName = strConcatAlloc(namespaceName, "_H");
        char *varName = "content";
        char *lenVarName = "contentLen";

        cppBakeRaw(&context, namespaceName, headerDefName, varName, lenVarName);

        free(headerDefName);
        free(namespaceName);
    } else if (javaIsFormatNameText(bakeFormat)) {
        char *packageName = "resources.baked";
        char *className = strFileNameNoExtAlphaAlloc(dstFileName);
        char *varName = "content";

        javaBakeText(&context, packageName, className, varName);

        free(className);
    } else if (javaIsFormatNameRaw(bakeFormat)) {
        char *packageName = "resources.baked";
        char *className = strFileNameNoExtAlphaAlloc(dstFileName);
        char *varName = "content";

        javaBakeRaw(&context, packageName, className, varName);

        free(className);
    } else {
        printf("Unknown bake format '%s'\n", bakeFormat);
        exitCode = EXIT_ERROR;   
    }

    if (contextHadErrors(&context)) {
        printf("I/O errors occurred\n");
        exitCode = EXIT_ERROR;
    }

    contextClose(&context);
    return exitCode;
}