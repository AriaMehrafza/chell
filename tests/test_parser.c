#include <assert.h>
#include <string.h>

#include "../src/parser.h"

int main(void)
{
  char **args = parse_line("hello dear world");

  assert(args != NULL);
  assert(strcmp(args[0], "hello") == 0);
  assert(strcmp(args[1], "dear") == 0);
  assert(strcmp(args[2], "world") == 0);
  assert(args[3] == NULL);

  free_args(args);

  return 0;
}
