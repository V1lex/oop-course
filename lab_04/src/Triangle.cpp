#include "Triangle.h"

#include <cmath>

Triangle::Triangle() = default;

Triangle::Triangle(Point a, Point b, Point c) {
    Point vertices[] = {a, b, c};
    set_vertices(vertices, 3);
}

const char* Triangle::name() const {
    return "Triangle";
}

std::size_t Triangle::vertex_count() const {
    return 3;
}

Figure* Triangle::clone() const {
    return new Triangle(*this);
}

bool Triangle::isEquilateral() const {
    const Point a = vertex(0);
    const Point b = vertex(1);
    const Point c = vertex(2);
    const double ab = std::hypot(b.x - a.x, b.y - a.y);
    const double bc = std::hypot(c.x - b.x, c.y - b.y);
    const double ca = std::hypot(a.x - c.x, a.y - c.y);
    return ab > eps && bc > eps && ca > eps &&
           std::abs(ab - bc) < eps && std::abs(bc - ca) < eps && std::abs(ca - ab) < eps;
}
