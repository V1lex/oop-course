#pragma once

#include "Figure.h"

class Pentagon : public Figure {
public:
    Pentagon();
    Pentagon(Point a, Point b, Point c, Point d, Point e);

    const char* name() const override;
    std::size_t vertex_count() const override;
    Figure* clone() const override;
    bool isRegular() const;
};
