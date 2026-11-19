#pragma once

#include "Figure.h"

class Triangle : public Figure {
public:
    Triangle();
    Triangle(Point a, Point b, Point c);

    const char* name() const override;
    std::size_t vertex_count() const override;
    Figure* clone() const override;
    bool isEquilateral() const;
};
