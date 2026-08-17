#ifndef BUILTIN_H
#define BUILTIN_H

enum builtin_result {
    NOT_BUILTIN,
    BUILTIN_OK,
    BUILTIN_ERROR,
    BUILTIN_EXIT
};

enum builtin_result builtin_cd(char **args);
enum builtin_result handle_builtin(char **args);

#endif
