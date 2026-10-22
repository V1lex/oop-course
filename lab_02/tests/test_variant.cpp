#include <gtest/gtest.h>

#include "my_string.h"

#include <utility>

TEST(StringConstructorTest, CreatesEmptyString) {
    String str;

    EXPECT_EQ(str, "");
}

TEST(StringConstructorTest, CopiesCStringIntoOwnBuffer) {
    char text[] = "Hello";
    String str(text);

    text[0] = 'h';

    EXPECT_EQ(str, "Hello");
}

TEST(StringCopyTest, CreatesIndependentCopy) {
    String original("Hello");
    String copy(original);

    copy.push_back('!');
    original.append(", World");

    EXPECT_EQ(original, "Hello, World");
    EXPECT_EQ(copy, "Hello!");
}

TEST(StringCopyTest, AssignsIndependentCopyAndReturnsReference) {
    String original("Hello");
    String copy("Old value");

    EXPECT_EQ(&(copy = original), &copy);
    copy.push_back('!');

    EXPECT_EQ(original, "Hello");
    EXPECT_EQ(copy, "Hello!");
}

TEST(StringCopyTest, SupportsSelfAssignment) {
    String str("Hello");
    const String& alias = str;

    str = alias;

    EXPECT_EQ(str, "Hello");
}

TEST(StringCopyTest, CopiesEmptyString) {
    String original;
    String copy(original);

    copy.push_back('x');

    EXPECT_EQ(original, "");
    EXPECT_EQ(copy, "x");
}

TEST(StringMoveTest, MovesStringAndResetsSource) {
    String original("Hello");
    String moved(std::move(original));

    EXPECT_EQ(moved, "Hello");
    EXPECT_EQ(original, "");

    original.push_back('x');

    EXPECT_EQ(original, "x");
    EXPECT_EQ(moved, "Hello");
}

TEST(StringMoveTest, MoveAssignmentResetsSourceAndReturnsReference) {
    String original("Hello");
    String assigned("Old value");

    EXPECT_EQ(&(assigned = std::move(original)), &assigned);

    EXPECT_EQ(assigned, "Hello");
    EXPECT_EQ(original, "");

    original.append("New");

    EXPECT_EQ(original, "New");
    EXPECT_EQ(assigned, "Hello");
}

TEST(StringPushBackTest, AppendsCharactersAcrossBufferGrowths) {
    String str;

    str.push_back('a');
    str.push_back('b');
    str.push_back('c');

    EXPECT_EQ(str, "abc");
}

TEST(StringAppendTest, AppendsStringsAndHandlesEmptyOperands) {
    String str;
    String empty;
    String suffix(", World");

    str.append(empty);

    EXPECT_EQ(str, "");

    str.append("Hello");
    str.append("");
    str.append(empty);
    str.append(suffix);
    str.append("!");

    EXPECT_EQ(str, "Hello, World!");
    EXPECT_EQ(suffix, ", World");
}

TEST(StringAppendTest, SupportsSelfAppend) {
    String str("abc");

    str.append(str);

    EXPECT_EQ(str, "abcabc");
}

TEST(StringFindTest, FindsFirstOccurrenceAndAcceptsCString) {
    String str("Hello, World! World!");

    EXPECT_EQ(str.find(String("World")), 7);
    EXPECT_EQ(str.find("World"), 7);
    EXPECT_EQ(str.find("Hello"), 0);
    EXPECT_EQ(str.find("!"), 12);
    EXPECT_EQ(str.find("absent"), String::npos);
    EXPECT_EQ(str.find(""), 0);
    EXPECT_EQ(String().find(""), 0);
    EXPECT_EQ(String().find("a"), String::npos);
}

TEST(StringCompareTest, ComparesCStringContentAndLength) {
    String str("abc");
    String empty;

    EXPECT_EQ(str, "abc");
    EXPECT_EQ(empty, "");
    EXPECT_FALSE(str == "abd");
    EXPECT_FALSE(str == "ab");
    EXPECT_FALSE(str == "abcd");
    EXPECT_FALSE(str == "");
    EXPECT_FALSE(empty == "a");
    EXPECT_TRUE(empty == nullptr);
    EXPECT_FALSE(str == nullptr);
}

TEST(StringRemoveCharTest, RemovesAllOccurrencesAndPreservesOriginal) {
    const String original("banana");
    String result = original.remove_char('a');

    EXPECT_EQ(result, "bnn");
    EXPECT_EQ(original, "banana");
}

TEST(StringRemoveCharTest, HandlesEmptyAndSingleCharacterStrings) {
    EXPECT_EQ(String().remove_char('a'), "");
    EXPECT_EQ(String("a").remove_char('a'), "");
    EXPECT_EQ(String("abc").remove_char('x'), "abc");
    EXPECT_EQ(String("aaa").remove_char('a'), "");
}
