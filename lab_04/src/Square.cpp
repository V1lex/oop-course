#include "Square.h"

#include <cmath>

Square::Square() = default;

Square::Square(Point a, Point b, Point c, Point d) {
    Point vertices[] = {a, b, c, d};
    set_vertices(vertices, 4);
}

const char* Square::name() const {
    return "Square";
}

std::size_t Square::vertex_count() const {
    return 4;
}

Figure* Square::clone() const {
    return new Square(*this);
}

double Square::side() const {
    const Point a = vertex(0);
    const Point b = vertex(1);
    return std::hypot(b.x - a.x, b.y - a.y);
}

bool Square::check_vertices(const Point* vertices) const {
    if (!Figure::check_vertices(vertices)) {
        return false;
    }
    const double side = std::hypot(vertices[1].x - vertices[0].x, vertices[1].y - vertices[0].y);
    for (std::size_t i = 1; i < vertex_count(); ++i) {
        const Point a = vertices[i];
        const Point b = vertices[(i + 1) % vertex_count()];
        const double length = std::hypot(b.x - a.x, b.y - a.y);
        if (std::abs(length - side) >= eps || std::abs(length / side - 1.0) >= eps) {
            return false;
        }
    }
    const double first = std::hypot(vertices[2].x - vertices[0].x, vertices[2].y - vertices[0].y);
    const double second = std::hypot(vertices[3].x - vertices[1].x, vertices[3].y - vertices[1].y);
    return std::abs(first - second) < eps && std::abs(first / second - 1.0) < eps;
}
