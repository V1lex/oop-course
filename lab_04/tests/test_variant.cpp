#include <gtest/gtest.h>

#include "FigureCollection.h"
#include "Pentagon.h"
#include "Square.h"
#include "Triangle.h"

#include <cmath>
#include <sstream>
#include <utility>

TEST(FigureTest, TriangleGeometry) {
    Triangle triangle({0, 0}, {4, 0}, {0, 3});
    EXPECT_DOUBLE_EQ(triangle.metric(), 6.0);
    EXPECT_DOUBLE_EQ(triangle.perimeter(), 12.0);
    EXPECT_NEAR(triangle.center().x, 4.0 / 3.0, Figure::eps);
    EXPECT_DOUBLE_EQ(triangle.center().y, 1.0);
    EXPECT_FALSE(triangle.isEquilateral());
    EXPECT_TRUE(Triangle({0, 0}, {2, 0}, {1, std::sqrt(3.0)}).isEquilateral());
}

TEST(FigureTest, SquareGeometry) {
    Square square({0, 0}, {2, 0}, {2, 2}, {0, 2});
    EXPECT_DOUBLE_EQ(square.metric(), 4.0);
    EXPECT_DOUBLE_EQ(square.perimeter(), 8.0);
    EXPECT_DOUBLE_EQ(square.side(), 2.0);
}

TEST(FigureTest, PentagonGeometry) {
    Pentagon pentagon({0, 0}, {2, 0}, {3, 2}, {1, 3}, {0, 1});
    EXPECT_DOUBLE_EQ(pentagon.metric(), 6.0);
    EXPECT_NEAR(pentagon.perimeter(), 3.0 + 3.0 * std::sqrt(5.0), Figure::eps);
    EXPECT_FALSE(pentagon.isRegular());

    Point vertices[5];
    for (int i = 0; i < 5; ++i) {
        double angle = 2.0 * std::acos(-1.0) * i / 5.0;
        vertices[i] = {std::cos(angle), std::sin(angle)};
    }
    Pentagon regular(vertices[0], vertices[1], vertices[2], vertices[3], vertices[4]);
    EXPECT_TRUE(regular.isRegular());
}

TEST(FigureTest, ReadsFromStream) {
    std::istringstream input("0 0 4 0 0 3");
    Triangle triangle;
    ASSERT_TRUE(input >> triangle);
    EXPECT_DOUBLE_EQ(triangle.metric(), 6.0);
}

TEST(FigureTest, WritesCoordinates) {
    Triangle triangle({0, 0}, {4, 0}, {0, 3});
    std::ostringstream output;
    output << triangle;
    EXPECT_EQ(output.str(), "0 0 4 0 0 3");
}

TEST(FigureTest, ComparesAreas) {
    Triangle triangle({0, 0}, {4, 0}, {0, 2});
    Square square({0, 0}, {2, 0}, {2, 2}, {0, 2});
    Triangle larger({0, 0}, {4, 0}, {0, 3});
    EXPECT_TRUE(triangle == square);
    EXPECT_FALSE(triangle == larger);
}

TEST(FigureTest, RejectsInvalidVertices) {
    Triangle triangle({0, 0}, {1, 1}, {2, 2});
    Square square({0, 0}, {2, 0}, {2, 1}, {0, 1});
    EXPECT_FALSE(triangle.valid());
    EXPECT_FALSE(square.valid());
}

TEST(FigureTest, AcceptsNegativeCoordinates) {
    Square square({-1, -1}, {1, -1}, {1, 1}, {-1, 1});
    EXPECT_TRUE(square.valid());
    EXPECT_DOUBLE_EQ(square.metric(), 4.0);
}

TEST(FigureCollectionTest, StoresDifferentTypes) {
    FigureCollection figures;
    figures.add(Triangle({0, 0}, {4, 0}, {0, 3}));
    figures.add(Square({0, 0}, {2, 0}, {2, 2}, {0, 2}));
    figures.add(Pentagon({0, 0}, {2, 0}, {3, 2}, {1, 3}, {0, 1}));
    EXPECT_EQ(figures.size(), 3u);
    EXPECT_DOUBLE_EQ(figures.total_metric(), 16.0);
    EXPECT_NE(dynamic_cast<Triangle*>(figures[0]), nullptr);
    EXPECT_EQ(dynamic_cast<Square*>(figures[0]), nullptr);
    EXPECT_TRUE(figures.remove(1));
    EXPECT_DOUBLE_EQ(figures.total_metric(), 12.0);
}

TEST(FigureCollectionTest, EmptyCollection) {
    FigureCollection figures;
    EXPECT_TRUE(figures.empty());
    EXPECT_DOUBLE_EQ(figures.total_metric(), 0.0);
    EXPECT_FALSE(figures.remove(0));
}

TEST(FigureCollectionTest, CopiesIndependently) {
    FigureCollection figures;
    figures.add(Triangle({0, 0}, {4, 0}, {0, 3}));
    FigureCollection copy = figures;
    figures.clear();
    EXPECT_DOUBLE_EQ(copy.total_metric(), 6.0);
}

TEST(FigureCollectionTest, MovesOwnership) {
    FigureCollection figures;
    figures.add(Triangle({0, 0}, {4, 0}, {0, 3}));
    FigureCollection moved = std::move(figures);
    EXPECT_TRUE(figures.empty());
    EXPECT_DOUBLE_EQ(moved.total_metric(), 6.0);
}

TEST(FigureTest, DeletesThroughBasePointer) {
    Figure* figure = new Triangle({0, 0}, {4, 0}, {0, 3});
    EXPECT_DOUBLE_EQ(figure->metric(), 6.0);
    delete figure;
}
