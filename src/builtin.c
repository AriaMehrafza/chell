#include "builtin.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

enum builtin_result builtin_cd(char **args)
{
    const char *path = args[1];

    if (path == NULL)
        path = getenv("HOME");

    if (path == NULL) {
        fprintf(stderr, "cd: HOME not set\n");
        return BUILTIN_ERROR;
    }

    if (path[0] == '~') {
        const char *home = getenv("HOME");

        if (home == NULL) {
            fprintf(stderr, "cd: HOME not set\n");
            return BUILTIN_ERROR;
        }

        char expanded[PATH_MAX];

        snprintf(expanded, sizeof(expanded), "%s%s", home, path + 1);

        path = expanded;
    }

    if (chdir(path) == -1) {
        perror("cd");
        return BUILTIN_ERROR;
    }

    return BUILTIN_OK;
}

enum builtin_result handle_builtin(char **args)
{
    if (strcmp(args[0], "exit") == 0)
        return BUILTIN_EXIT;

    if (strcmp(args[0], "cd") == 0)
        return builtin_cd(args);

    return NOT_BUILTIN;
}
