#include "unity.h" // compile/link in Unity test framework
#include <string.h>
#include "string_search.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_findSubString(void)
{
    TEST_ASSERT_EQUAL_INT(-1, indexOfSubStr("Hi", "Hello"));
    TEST_ASSERT_EQUAL_INT(-1, indexOfSubStr("Hello", "Hi"));
    TEST_ASSERT_EQUAL_INT(0, indexOfSubStr("Hello", "Hell"));
    TEST_ASSERT_EQUAL_INT(2, indexOfSubStr("Hello", "ll"));
    TEST_ASSERT_EQUAL_INT(-1, indexOfSubStr("Hello", "elo"));
}