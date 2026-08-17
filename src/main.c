#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

#include "parser.h"
#include "executor.h"
#include "builtin.h"

void print_prompt(void)
{
    char hostname[HOST_NAME_MAX];
    char cwd[PATH_MAX];

    const char *username = getenv("USER");

    if (username == NULL)
        username = "unknown";

    if (gethostname(hostname, sizeof(hostname)) == -1)
        snprintf(hostname, sizeof(hostname), "unknown");

    if (getcwd(cwd, sizeof(cwd)) == NULL)
        snprintf(cwd, sizeof(cwd), "?");

    printf("%s@%s:%s$ ", username, hostname, cwd);
    fflush(stdout);
}

int main()
{
	char *line = NULL;
	size_t capacity = 0;

	while (1) {
        print_prompt();

		ssize_t nread = getline(&line, &capacity, stdin);

		if (nread == -1)
			break;

		char **args = parse_line(line);

		if (!args)
			continue;

		if (args[0] == NULL)
			continue;
		
        enum builtin_result result = handle_builtin(args);

        if (result == BUILTIN_EXIT) {
            free_args(args);
            break;
        }

        if (result != NOT_BUILTIN) {
            free_args(args);
            continue;
        }

		execute(args);

		free_args(args);
	}

	free(line);

	return 0;
}
