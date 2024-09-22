#include <gtest/gtest.h>
#include "SaferArray.hpp"

// Sample class for use with SaferArray
class TestClass
{
public:
    TestClass(int val) : value(val) {}
    int getValue() const { return value; }

private:
    int value;
};

// Test suite for SaferArray
template <typename T, int MaxSize>
class SaferArrayTest : public ::testing::Test
{
protected:
    SaferArray<T, MaxSize> array;
};

// Define test types and sizes
using SaferArrayInt = SaferArray<TestClass, 5>;

using SaferArrayTestInt = SaferArrayTest<TestClass, 5>;

// Test adding elements
TEST_F(SaferArrayTestInt, AddElements)
{
    TestClass obj1(1), obj2(2), obj3(3);
    EXPECT_TRUE(array.add(&obj1));
    EXPECT_TRUE(array.add(&obj2));
    EXPECT_TRUE(array.add(&obj3));
    EXPECT_EQ(array.size(), 3);
}

// Test adding more elements than capacity
TEST_F(SaferArrayTestInt, AddTooManyElements)
{
    TestClass objs[6] = {TestClass(1), TestClass(2), TestClass(3), TestClass(4), TestClass(5), TestClass(6)};
    for (int i = 0; i < 5; ++i)
    {
        EXPECT_TRUE(array.add(&objs[i]));
    }
    EXPECT_FALSE(array.add(&objs[5])); // should fail as array is full
}

// Test removing elements
TEST_F(SaferArrayTestInt, RemoveElement)
{
    TestClass obj1(1), obj2(2), obj3(3);
    array.add(&obj1);
    array.add(&obj2);
    array.add(&obj3);

    EXPECT_TRUE(array.remove(&obj2));
    EXPECT_EQ(array.size(), 2);
    EXPECT_EQ(array[0]->getValue(), 1);
    EXPECT_EQ(array[1]->getValue(), 3);
}

// Test removing an element that does not exist
TEST_F(SaferArrayTestInt, RemoveNonexistentElement)
{
    TestClass obj1(1), obj2(2), obj3(3);
    array.add(&obj1);
    array.add(&obj2);

    TestClass obj4(4);
    EXPECT_FALSE(array.remove(&obj4)); // should fail as obj4 was not added
}

// Test accessing elements by index
TEST_F(SaferArrayTestInt, AccessElementByIndex)
{
    TestClass obj1(1), obj2(2);
    array.add(&obj1);
    array.add(&obj2);

    EXPECT_EQ(array[0]->getValue(), 1);
    EXPECT_EQ(array[1]->getValue(), 2);
    EXPECT_EQ(array[2], nullptr); // Out of bounds access
}

// Test accessing elements with out-of-bounds index
TEST_F(SaferArrayTestInt, AccessOutOfBounds)
{
    EXPECT_EQ(array[0], nullptr); // No elements added yet
}

// Test write access to elements
TEST_F(SaferArrayTestInt, WriteAccess)
{
    TestClass obj1(1), obj2(2);
    array.add(&obj1);
    array.add(&obj2);

    array[1] = &obj1;                   // Overwrite element
    EXPECT_EQ(array[1]->getValue(), 1); // Should be same as obj1 value
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}