#include "parser.h"

#include <stdlib.h>
#include <string.h>

#define MAX_ARGS 64

char **parse_line(char *line)
{
  char **args = malloc(sizeof(char *) * MAX_ARGS);

  if (!args)
    return NULL;

  int argc = 0;

  char *copy = strdup(line);

  if (!copy) {
    free(args);
    return NULL;
  }

  char *token = strtok(copy, " \t\n");

  while (token && argc < MAX_ARGS - 1) {
    args[argc] = strdup(token);

    if (!args[argc]) {
      free_args(args);
      free(copy);
      return NULL;
    }

    argc++;
    token = strtok(NULL, " \t\n");
  }

  args[argc] = NULL;

  free(copy);

  return args;
}

void free_args(char **args)
{
  if (!args)
    return;

  for (int i = 0; args[i]; i++)
    free(args[i]);

  free(args);
}
