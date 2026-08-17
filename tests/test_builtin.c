#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../src/builtin.h"

static void test_cd(void)
{
    char original[4096];

    assert(getcwd(original, sizeof(original)) != NULL);

    char *args[] = {"cd", "/", NULL};

    assert(builtin_cd(args) == BUILTIN_OK);

    char cwd[4096];
    assert(getcwd(cwd, sizeof(cwd)) != NULL);
    assert(strcmp(cwd, "/") == 0);

    assert(chdir(original) == 0);
}

static void test_cd_home(void)
{
    char original[4096];

    assert(getcwd(original, sizeof(original)) != NULL);

    char *args[] = {"cd", NULL};

    assert(builtin_cd(args) == BUILTIN_OK);

    const char *home = getenv("HOME");

    if (home != NULL) {
        char cwd[4096];

        assert(getcwd(cwd, sizeof(cwd)) != NULL);
        assert(strcmp(cwd, home) == 0);
    }

    assert(chdir(original) == 0);
}

static void test_cd_tilde(void)
{
    char original[4096];

    assert(getcwd(original, sizeof(original)) != NULL);

    char *args[] = {"cd", "~", NULL};

    assert(builtin_cd(args) == BUILTIN_OK);

    const char *home = getenv("HOME");

    if (home != NULL) {
        char cwd[4096];

        assert(getcwd(cwd, sizeof(cwd)) != NULL);
        assert(strcmp(cwd, home) == 0);
    }

    assert(chdir(original) == 0);
}

static void test_cd_nonexistent(void)
{
    char *args[] = {"cd", "/this/path/does/not/exist", NULL};

    assert(builtin_cd(args) == BUILTIN_ERROR);
}

static void test_handle_builtin(void)
{
    char *exit_args[] = {"exit", NULL};
    char *cd_args[] = {"cd", "/", NULL};
    char *unknown_args[] = {"ls", NULL};

    assert(handle_builtin(exit_args) == BUILTIN_EXIT);
    assert(handle_builtin(cd_args) == BUILTIN_OK);
    assert(handle_builtin(unknown_args) == NOT_BUILTIN);
}

int main(void)
{
    test_cd();
    test_cd_home();
    test_cd_tilde();
    test_cd_nonexistent();
    test_handle_builtin();

    return 0;
}
