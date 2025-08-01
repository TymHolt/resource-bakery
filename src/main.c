#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "format/cpp/format_cpp.h"

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

    char *srcFile;
    if (!tryArgsGetNext(&args, &srcFile)) {
        printf("No source file given\n");
        printUsage(execName);
        return EXIT_ERROR;
    }

    char *dstFile;
    if (!tryArgsGetNext(&args, &dstFile)) {
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
    if (!tryContextOpen(srcFile, dstFile, &context)) {
        printf("Could not create baking context\n");
        return EXIT_ERROR;
    }

    int exitCode = EXIT_SUCCESS;

    if (cppIsFormatName(bakeFormat)) {
        cppBake(&context, dstFile);
    } else {
        printf("Unknown bake format '%s'\n", bakeFormat);
        exitCode = EXIT_ERROR;   
    }

    contextClose(&context);
    return exitCode;
}