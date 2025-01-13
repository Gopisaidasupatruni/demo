#include "../unity/unity.h"  
#include "../src/calc.h"
void setUp() {}
void tearDown() {}

void test_add(void)
{
    int result = add(10, 20);
    TEST_ASSERT_EQUAL(30, result);
}

void test_sub(void)
{
    int result = sub(20, 10);
    TEST_ASSERT_EQUAL(10, result);
}


int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_add);
    RUN_TEST(test_sub);

    UNITY_END();

    return 0;
}

