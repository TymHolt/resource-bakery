#include <stdbool.h>
#include <stdio.h>
#include <string.h>

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

int main(int argc, char **argv) {
    Args args;
    args.argc = argc;
    args.argv = argv;
    args.argi = 0;

    char *execName;
    if (!tryArgsGetNext(&args, &execName)) {
        printf("No executable name given\n");
        printUsage("bake");
        return -1;
    }

    char *bakeFormat;
    if (!tryArgsGetNext(&args, &bakeFormat)) {
        printf("No bake format given\n");
        printUsage(execName);
        return -1;
    }

    char *srcFile;
    if (!tryArgsGetNext(&args, &srcFile)) {
        printf("No source file given\n");
        printUsage(execName);
        return -1;
    }

    char *dstFile;
    if (!tryArgsGetNext(&args, &dstFile)) {
        printf("No destination file given\n");
        printUsage(execName);
        return -1;
    }

    if (argsHasMore(&args)) {
        printf("Too many arguments\n");
        printUsage(execName);
        return -1;
    }

    if (strcmp(bakeFormat, "cpp") != 0 && strcmp(bakeFormat, "c++") != 0) {
        printf("Unknown bake format '%s'\n", bakeFormat);
        return -1;
    }

    printf("Arguments\nFormat: '%s'\nSrc: '%s'\nDst: '%s'\n", bakeFormat, srcFile, dstFile);
    return 0;
}