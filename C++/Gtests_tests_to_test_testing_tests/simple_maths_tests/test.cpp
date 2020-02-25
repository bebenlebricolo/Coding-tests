#include "simple_maths.hpp"
#include <gtest/gtest.h>

using namespace SimpleMaths;

TEST(SimpleMathsTest, addTest)
{
    ASSERT_EQ(6, add<uint32_t>(4,2));
    ASSERT_EQ(11, add<uint32_t>(4,7));
    ASSERT_EQ(0, add<int32_t>(4,-4));
    ASSERT_EQ(-10, add<int32_t>(4,-14));

}

TEST(SimpleMathsTest, multiplyTest)
{
    ASSERT_EQ(8, multiply<uint32_t>(4,2));
    ASSERT_EQ(-12, multiply<int>(4,-3));
    ASSERT_NE(140, multiply<char>(6,5));
}

TEST(SimpleMathsTest, divideTest)
{
    ASSERT_EQ(2, divide<uint32_t>(4,2));
    ASSERT_NO_THROW(divide<uint32_t>(3,4));
    ASSERT_THROW(divide<uint32_t>(3,0), exceptions::CannotDivideByZero);
}

TEST(SimpleMathsTest, substractTest)
{
    ASSERT_EQ(2, substract<uint32_t>(4,2));
    ASSERT_FLOAT_EQ(-1.1,substract<float>(3.8,4.9));
}

TEST(SimpleMathsTest, moduloTest)
{
    ASSERT_EQ(0, modulo<uint32_t>(4,2));
    ASSERT_EQ(8,modulo<int>(45,37));
    ASSERT_EQ(45,modulo<uint32_t>(45,-37));
}

int main(int argc, char** argv)
{
    add<uint32_t>(32U,65U);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
