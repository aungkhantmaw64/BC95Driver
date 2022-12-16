#include "StringSearch.h"
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>

int findSubstringIndex(const char *main_str, const char *sub_str)
{
  char *temp = strstr(main_str, sub_str);
  if (!temp)
    return -1;
  return temp - main_str;
}
