#include <gtest/gtest.h>

#include "array_ops.h"

TEST(ArrayCreateTest, CreatesZeroInitializedArray) {
    std::size_t size = 5;
    int* arr = array_create(size);

    ASSERT_NE(arr, nullptr);

    for (std::size_t i = 0; i < size; ++i) {
        EXPECT_EQ(arr[i], 0);
    }

    array_delete(arr);
}

TEST(ArrayCreateTest, ReturnsNullptrForZeroSize) {
    std::size_t size = 0;
    int* arr = array_create(size);

    EXPECT_EQ(arr, nullptr);
}

TEST(ArrayDeleteTest, DeletesArrayAndSetsNullptr) {
    std::size_t size = 5;
    int* arr = array_create(size);

    array_delete(arr);

    EXPECT_EQ(arr, nullptr);
}

TEST(ArrayResizeTest, IncreasesArraySize) {
    std::size_t size = 5;
    int* arr = array_create(size);

    for (std::size_t i = 0; i < size; ++i) {
        arr[i] = static_cast<int>(i + 1);
    }

    std::size_t new_size = 10;
    arr = array_resize(arr, size, new_size);
    size = new_size;

    ASSERT_NE(arr, nullptr);
    EXPECT_EQ(size, 10);

    for (std::size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(arr[i], static_cast<int>(i + 1));
    }

    for (std::size_t i = 5; i < size; ++i) {
        EXPECT_EQ(arr[i], 0);
    }

    array_delete(arr);
}

TEST(ArrayResizeTest, DecreasesArraySize) {
    std::size_t size = 10;
    int* arr = array_create(size);

    for (std::size_t i = 0; i < size; ++i) {
        arr[i] = static_cast<int>(i + 1);
    }

    std::size_t new_size = 5;
    arr = array_resize(arr, size, new_size);
    size = new_size;

    ASSERT_NE(arr, nullptr);
    EXPECT_EQ(size, 5);

    for (std::size_t i = 0; i < size; ++i) {
        EXPECT_EQ(arr[i], static_cast<int>(i + 1));
    }

    array_delete(arr);
}

TEST(ArrayResizeTest, ResizesArrayToZero) {
    std::size_t size = 5;
    int* arr = array_create(size);

    std::size_t new_size = 0;
    arr = array_resize(arr, size, new_size);
    size = new_size;

    EXPECT_EQ(arr, nullptr);
    EXPECT_EQ(size, 0);
}

TEST(ArrayInsertTest, InsertsElementAtBeginning) {
    std::size_t size = 5;
    int* arr = array_create(size);

    std::size_t pos = 0;
    int value = 77;
    arr = array_insert(arr, size, pos, value);

    ASSERT_NE(arr, nullptr);
    EXPECT_EQ(size, 6);
    EXPECT_EQ(arr[pos], value);

    array_delete(arr);
}

TEST(ArrayInsertTest, InsertsElementIntoMiddle) {
    std::size_t size = 5;
    int* arr = array_create(size);

    for (std::size_t i = 0; i < size; ++i) {
        arr[i] = static_cast<int>(i + 1);
    }

    std::size_t pos = 2;
    int value = 77;
    arr = array_insert(arr, size, pos, value);

    ASSERT_NE(arr, nullptr);
    EXPECT_EQ(size, 6);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 77);
    EXPECT_EQ(arr[3], 3);
    EXPECT_EQ(arr[4], 4);
    EXPECT_EQ(arr[5], 5);

    array_delete(arr);
}

TEST(ArrayInsertTest, InsertsElementAtEnd) {
    std::size_t size = 5;
    int* arr = array_create(size);

    std::size_t pos = size;
    int value = 77;
    arr = array_insert(arr, size, pos, value);

    ASSERT_NE(arr, nullptr);
    EXPECT_EQ(size, 6);
    EXPECT_EQ(arr[pos], value);

    array_delete(arr);
}

TEST(ArrayRemoveTest, RemovesElementFromMiddle) {
    std::size_t size = 5;
    int* arr = array_create(size);

    for (std::size_t i = 0; i < size; ++i) {
        arr[i] = static_cast<int>(i + 1);
    }

    std::size_t pos = 2;
    arr = array_remove(arr, size, pos);

    ASSERT_NE(arr, nullptr);
    EXPECT_EQ(size, 4);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 4);
    EXPECT_EQ(arr[3], 5);

    array_delete(arr);
}

TEST(ArrayRemoveTest, RemovesLastElement) {
    std::size_t size = 5;
    int* arr = array_create(size);

    for (std::size_t i = 0; i < size; ++i) {
        arr[i] = static_cast<int>(i + 1);
    }

    std::size_t pos = size - 1;
    arr = array_remove(arr, size, pos);

    ASSERT_NE(arr, nullptr);
    EXPECT_EQ(size, 4);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[3], 4);

    array_delete(arr);
}

TEST(CountingSortTest, SortsArray) {
    std::size_t size = 5;
    int* arr = array_create(size);

    arr[0] = 5;
    arr[1] = 3;
    arr[2] = 1;
    arr[3] = 4;
    arr[4] = 2;

    array_counting_sort(arr, size);

    for (std::size_t i = 0; i < size; ++i) {
        EXPECT_EQ(arr[i], static_cast<int>(i + 1));
    }

    array_delete(arr);
}

TEST(CountingSortTest, SortsArrayWithDuplicates) {
    std::size_t size = 5;
    int* arr = array_create(size);

    arr[0] = 3;
    arr[1] = 1;
    arr[2] = 4;
    arr[3] = 1;
    arr[4] = 5;

    array_counting_sort(arr, size);

    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 1);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[3], 4);
    EXPECT_EQ(arr[4], 5);

    array_delete(arr);
}

TEST(CountingSortTest, SortsSingleElementArray) {
    std::size_t size = 1;
    int* arr = array_create(size);

    arr[0] = 77;

    array_counting_sort(arr, size);

    EXPECT_EQ(arr[0], 77);

    array_delete(arr);
}

TEST(RangeCountTest, CountsElementsInRange) {
    std::size_t size = 5;
    int* arr = array_create(size);

    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr[3] = 4;
    arr[4] = 5;

    std::size_t count = array_range_count(arr, size, 2, 4);

    EXPECT_EQ(count, 3);

    array_delete(arr);
}

TEST(RangeCountTest, CountsSingleElementInRange) {
    std::size_t size = 1;
    int* arr = array_create(size);

    arr[0] = 77;

    std::size_t count = array_range_count(arr, size, 77, 77);

    EXPECT_EQ(count, 1);

    array_delete(arr);
}

TEST(RangeCountTest, IncludesRangeBoundaries) {
    std::size_t size = 5;
    int* arr = array_create(size);

    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr[3] = 4;
    arr[4] = 5;

    std::size_t count = array_range_count(arr, size, 1, 5);

    EXPECT_EQ(count, 5);

    array_delete(arr);
}

TEST(RangeCountTest, ReturnsZeroWhenNoElementsInRange) {
    std::size_t size = 5;
    int* arr = array_create(size);

    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr[3] = 4;
    arr[4] = 5;

    std::size_t count = array_range_count(arr, size, 6, 10);

    EXPECT_EQ(count, 0);

    array_delete(arr);
}