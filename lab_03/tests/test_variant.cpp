#include <gtest/gtest.h>

#include "IPAddress.h"
#include "IPAddressSet.h"

#include <utility>

TEST(IPAddressSetTest, CreatesEmptySet) {
    IPAddressSet set;

    EXPECT_EQ(set.size(), 0u);
    EXPECT_FALSE(set.contains(IPAddress(1, 2, 3, 4)));
}

TEST(IPAddressSetTest, AddsAddressAndRejectsDuplicate) {
    IPAddressSet set;
    IPAddress ip(192, 168, 1, 1);

    EXPECT_TRUE(set.add(ip));
    EXPECT_FALSE(set.add(ip));
    EXPECT_EQ(set.size(), 1u);
}

TEST(IPAddressSetTest, StoresAddressesInNumericOrder) {
    IPAddressSet set;
    set.add(IPAddress(10, 0, 0, 1));
    set.add(IPAddress(2, 0, 0, 1));
    set.add(IPAddress());

    EXPECT_EQ(set[0], IPAddress(0, 0, 0, 0));
    EXPECT_EQ(set[1], IPAddress(2, 0, 0, 1));
    EXPECT_EQ(set[2], IPAddress(10, 0, 0, 1));
}

TEST(IPAddressSetTest, RejectsInvalidOctets) {
    IPAddressSet set;

    EXPECT_FALSE(set.add(IPAddress(-1, 0, 0, 1)));
    EXPECT_FALSE(set.add(IPAddress(192, 168, 1, 256)));
}

TEST(IPAddressSetTest, RemovesAddressAndPreservesOrder) {
    IPAddressSet set;
    set.add(IPAddress(1, 0, 0, 1));
    set.add(IPAddress(2, 0, 0, 1));
    set.add(IPAddress(3, 0, 0, 1));

    EXPECT_TRUE(set.remove(IPAddress(2, 0, 0, 1)));
    EXPECT_FALSE(set.remove(IPAddress(2, 0, 0, 1)));
    EXPECT_EQ(set[1], IPAddress(3, 0, 0, 1));
}

TEST(IPAddressSetTest, ChecksMembership) {
    IPAddressSet set;
    IPAddress ip(192, 168, 1, 1);
    set.add(ip);

    EXPECT_TRUE(set.contains(ip));
    EXPECT_TRUE(set(ip));
    EXPECT_FALSE(set(IPAddress(10, 0, 0, 1)));
}

TEST(IPAddressSetTest, CreatesIndependentCopy) {
    IPAddressSet original;
    original.add(IPAddress(1, 2, 3, 4));
    IPAddressSet copy(original);

    copy.remove(IPAddress(1, 2, 3, 4));

    EXPECT_EQ(original.size(), 1u);
    EXPECT_TRUE(copy.empty());
}

TEST(IPAddressSetTest, MovesSetAndEmptiesSource) {
    IPAddressSet original;
    original.add(IPAddress(1, 2, 3, 4));

    IPAddressSet moved(std::move(original));

    EXPECT_TRUE(moved.contains(IPAddress(1, 2, 3, 4)));
    EXPECT_TRUE(original.empty());
}

TEST(IPAddressSetTest, PerformsSetOperations) {
    IPAddressSet first;
    first.add(IPAddress(1, 0, 0, 1));
    first.add(IPAddress(2, 0, 0, 1));
    IPAddressSet second;
    second.add(IPAddress(2, 0, 0, 1));
    second.add(IPAddress(3, 0, 0, 1));

    IPAddressSet united(first);
    united.add(IPAddress(3, 0, 0, 1));
    IPAddressSet common;
    common.add(IPAddress(2, 0, 0, 1));
    IPAddressSet difference;
    difference.add(IPAddress(1, 0, 0, 1));

    EXPECT_EQ(first | second, united);
    EXPECT_EQ(first & second, common);
    EXPECT_EQ(first - second, difference);
}

TEST(IPAddressSetTest, ComparesSets) {
    IPAddressSet first;
    first.add(IPAddress(1, 2, 3, 4));
    IPAddressSet second(first);

    EXPECT_TRUE(first == second);
    EXPECT_FALSE(first != second);

    second.add(IPAddress(5, 6, 7, 8));
    EXPECT_TRUE(first != second);
}

TEST(IPAddressSetTest, PrintsSet) {
    IPAddressSet set;
    set.add(IPAddress(192, 168, 1, 1));
    set.add(IPAddress(10, 0, 0, 1));

    EXPECT_EQ(testing::PrintToString(set), "{ 10.0.0.1, 192.168.1.1 }");
}

TEST(IPAddressSetTest, Adds1000AddressesWithoutDuplicates) {
    IPAddressSet set;

    // 1000 разных адресов
    for (int i = 0; i < 1000; ++i) {
        set.add(IPAddress(10, 0, i / 256, i % 256));
    }

    EXPECT_EQ(set.size(), 1000u);

    for (int i = 0; i < 1000; ++i) {
        set.add(IPAddress(10, 0, i / 256, i % 256));
    }

    EXPECT_EQ(set.size(), 1000u);
}
