#include <assert.h>
#include <string.h>

#include "../src/parser.h"

static void test_basic(void)
{
    char **args = parse_line("hello dear world");

    assert(args != NULL);
    assert(strcmp(args[0], "hello") == 0);
    assert(strcmp(args[1], "dear") == 0);
    assert(strcmp(args[2], "world") == 0);
    assert(args[3] == NULL);

    free_args(args);
}

static void test_single_argument(void)
{
    char **args = parse_line("hello");

    assert(args != NULL);
    assert(strcmp(args[0], "hello") == 0);
    assert(args[1] == NULL);

    free_args(args);
}

static void test_empty_line(void)
{
    char **args = parse_line("");

    assert(args != NULL);
    assert(args[0] == NULL);

    free_args(args);
}

static void test_whitespace(void)
{
    char **args = parse_line("   hello   world   ");

    assert(args != NULL);
    assert(strcmp(args[0], "hello") == 0);
    assert(strcmp(args[1], "world") == 0);
    assert(args[2] == NULL);

    free_args(args);
}

static void test_command(void)
{
    char **args = parse_line("echo hello world");

    assert(args != NULL);
    assert(strcmp(args[0], "echo") == 0);
    assert(strcmp(args[1], "hello") == 0);
    assert(strcmp(args[2], "world") == 0);
    assert(args[3] == NULL);

    free_args(args);
}

int main(void)
{
    test_basic();
    test_single_argument();
    test_empty_line();
    test_whitespace();
    test_command();

    return 0;
}
