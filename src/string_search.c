#include "string_search.h"

#define MAX_STR_LENGTH 50

int indexOfSubStr(const char *main_str, const char *sub_str)
{
    char *temp = strstr(main_str, sub_str);
    if (temp == NULL)
        return -1;
    return temp - main_str;
}