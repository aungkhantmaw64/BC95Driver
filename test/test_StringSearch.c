#ifdef TEST

#include "unity.h"

#include "StringSearch.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_StringSearch(void)
{
    TEST_ASSERT_EQUAL_INT(-1, findSubstringIndex("Hello", "Holla"));
    TEST_ASSERT_EQUAL_INT(2, findSubstringIndex("Hello", "llo"));
    TEST_ASSERT_EQUAL_INT(4, findSubstringIndex("Hello", "o"));
    TEST_ASSERT_EQUAL_INT(-1, findSubstringIndex("Hello", "A"));
    TEST_ASSERT_EQUAL_INT(1, findSubstringIndex("Hello", "ell"));
    TEST_ASSERT_EQUAL_INT(2, findSubstringIndex("Hello", "l"));
    TEST_ASSERT_EQUAL_INT(2, findSubstringIndex("\r\nREBOOT\r\n", "REBOOT"));
}

#endif // TEST
