#include "Pentagon.h"

#include <cmath>

Pentagon::Pentagon() = default;

Pentagon::Pentagon(Point a, Point b, Point c, Point d, Point e) {
    Point vertices[] = {a, b, c, d, e};
    set_vertices(vertices, 5);
}

const char* Pentagon::name() const {
    return "Pentagon";
}

std::size_t Pentagon::vertex_count() const {
    return 5;
}

Figure* Pentagon::clone() const {
    return new Pentagon(*this);
}

bool Pentagon::isRegular() const {
    const Point first = vertex(0);
    const Point second = vertex(1);
    const Point third = vertex(2);
    const double side = std::hypot(second.x - first.x, second.y - first.y);
    const double diagonal = std::hypot(third.x - first.x, third.y - first.y);
    if (side <= eps || diagonal <= side) {
        return false;
    }

    for (std::size_t i = 0; i < vertex_count(); ++i) {
        const Point a = vertex(i);
        const Point b = vertex((i + 1) % vertex_count());
        const Point c = vertex((i + 2) % vertex_count());
        const double ab = std::hypot(b.x - a.x, b.y - a.y);
        const double ac = std::hypot(c.x - a.x, c.y - a.y);
        if (ab <= eps || !(std::abs(ab - side) < eps) || !(std::abs(ac - diagonal) < eps)) {
            return false;
        }
    }
    return true;
}
