#include "../include/JsonDocument.h"
#include <gtest/gtest.h>
#include "gmock/gmock.h"

using namespace std;
using namespace Json;


TEST(test, copyConstructor_worksOnSafeCopy)
{
    Json::JsonArray array;

    // Create a safe copy of the original JsonArray
    Json::JsonArray copy(array);

    // Add a new element to the original JsonArray
    array.put(23);
    ASSERT_TRUE(copy.size() == 0);
}

TEST(test, isEmpty_isTrueAfterCreation)
{
    Json::JsonArray array;

    ASSERT_TRUE(array.size() == 0);
}

TEST(test, isEmpty_isFalseAfterAdd)
{
    Json::JsonArray array;
    array.put(true);
    ASSERT_FALSE(array.size() == 0);
}

TEST(test, size_isOneAfterAdd)
{
    Json::JsonArray array;
    array.put(true);
    ASSERT_EQ(1, array.size());
}

TEST(test, values_containsValueAfterAdd)
{
    Json::JsonArray array;
    array.put(true);
    ASSERT_EQ(1, array.size());
    ASSERT_EQ("true", array.get(0)->toString());
}

TEST(test, size_isZeroAfterCreation)
{
    Json::JsonArray array;
    ASSERT_TRUE(array.size() == 0);
}

TEST(test, get_failsWithInvalidIndex)
{
    Json::JsonArray array;
    ASSERT_ANY_THROW(array.get(0));
}

TEST(test, add_int)
{
    Json::JsonArray array;
    array.put(23);
    ASSERT_EQ("[23]", array.toString());
}

TEST(test, add_double)
{
    Json::JsonArray array;
    array.put(3.14);
    ASSERT_EQ("[3.14]", array.toString());
}

TEST(test, add_boolean)
{
    Json::JsonArray array;
    array.put(true);
    ASSERT_EQ("[true]", array.toString());
}

// issue
TEST(test, add_string)
{
    Json::JsonArray array;
    array.put("foo");
    // ASSERT_EQ("[\"foo\"]", array.toString());
}

TEST(test, add_jsonNull)
{
    Json::JsonArray array;
    array.put();
    ASSERT_EQ("[null]", array.toString());
}

TEST(test, add_jsonArray)
{
    Json::JsonArray innerArray;
    Json::JsonArray array;
    array.put(std::make_shared<Json::JsonArray>(innerArray));
    ASSERT_EQ("[[]]", array.toString());
}

TEST(test, add_json_nestedArray)
{
    Json::JsonArray array;
    Json::JsonArray innerArray;
    innerArray.put(23);
    array.put(std::make_shared<Json::JsonArray>(innerArray));
    ASSERT_EQ("[[23]]", array.toString());
}

TEST(test, add_json_nestedArray_modifiedAfterAdd)
{
    Json::JsonArray array;
    auto innerArray = std::make_shared<Json::JsonArray>();
    array.put(innerArray);
    innerArray->put(23);
    ASSERT_EQ("[[23]]", array.toString());
}

TEST(test, add_json_nestedObject)
{
    Json::JsonArray array;
    JsonObject innerObject;
    innerObject.put("a", 23);

    array.put(std::make_shared<Json::JsonObject>(innerObject));
    ASSERT_EQ("[{\"a\":23}]", array.toString());
}

TEST(test, add_json_nestedObject_modifiedAfterAdd)
{
    Json::JsonArray array;
    auto innerObject = std::make_shared<Json::JsonObject>();
    array.put(innerObject);
    innerObject->put("a", 23);
    ASSERT_EQ("[{\"a\":23}]", array.toString());
}

GTEST_API_ int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
