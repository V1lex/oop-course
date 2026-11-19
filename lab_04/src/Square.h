#pragma once

#include "Figure.h"

class Square : public Figure {
public:
    Square();
    Square(Point a, Point b, Point c, Point d);

    const char* name() const override;
    std::size_t vertex_count() const override;
    Figure* clone() const override;
    double side() const;

    bool check_vertices(const Point* vertices) const override;
};
