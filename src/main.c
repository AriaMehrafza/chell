#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "parser.h"

int main()
{
  char *line = NULL;
  size_t capacity = 0;

  while (1) {
    printf("> ");
    fflush(stdout);

    ssize_t nread = getline(&line, &capacity, stdin);

    if (nread == -1)
      break;

    char **args = parse_line(line);

    if (!args)
      continue;

    for (int i = 0; args[i]; i++)
      printf("argv[%d] =\"%s\"\n", i, args[i]);

    free_args(args);
  }

  free(line);

  return 0;
}
