#include "Figure.h"

#include <algorithm>
#include <cmath>

double orientation(Point a, Point b, Point c) {
    const double length = std::hypot(b.x - a.x, b.y - a.y);
    return (b.x - a.x) / length * (c.y - a.y) - (b.y - a.y) / length * (c.x - a.x);
}

bool intersects(Point a, Point b, Point c, Point d) {
    const double eps = Figure::eps;
    if (std::max(a.x, b.x) < std::min(c.x, d.x) - eps ||
        std::max(c.x, d.x) < std::min(a.x, b.x) - eps ||
        std::max(a.y, b.y) < std::min(c.y, d.y) - eps ||
        std::max(c.y, d.y) < std::min(a.y, b.y) - eps) {
        return false;
    }
    const double first = orientation(a, b, c);
    const double second = orientation(a, b, d);
    const double third = orientation(c, d, a);
    const double fourth = orientation(c, d, b);
    if ((first > eps && second > eps) || (first < -eps && second < -eps) ||
        (third > eps && fourth > eps) || (third < -eps && fourth < -eps)) {
        return false;
    }
    return true;
}

Figure::Figure() : vertices_(nullptr) {}

Figure::Figure(const Figure& other)
    : vertices_(other.vertices_ == nullptr ? nullptr : new Point[other.vertex_count()]) {
    if (vertices_ != nullptr) {
        for (std::size_t i = 0; i < other.vertex_count(); ++i) {
            vertices_[i] = other.vertices_[i];
        }
    }
}

Figure::Figure(Figure&& other) noexcept : vertices_(other.vertices_) {
    other.vertices_ = nullptr;
}

Figure& Figure::operator=(const Figure& other) {
    if (this != &other) {
        Point* copy = other.vertices_ == nullptr ? nullptr : new Point[other.vertex_count()];
        if (copy != nullptr) {
            for (std::size_t i = 0; i < other.vertex_count(); ++i) {
                copy[i] = other.vertices_[i];
            }
        }
        delete[] vertices_;
        vertices_ = copy;
    }
    return *this;
}

Figure& Figure::operator=(Figure&& other) noexcept {
    if (this != &other) {
        delete[] vertices_;
        vertices_ = other.vertices_;
        other.vertices_ = nullptr;
    }
    return *this;
}

Figure::~Figure() {
    delete[] vertices_;
}

void Figure::set_vertices(const Point* vertices, std::size_t count) {
    if (count != vertex_count() || !check_vertices(vertices)) {
        std::cerr << "Ошибка: точки не образуют " << name() << '\n';
        return;
    }
    Point* copy = new Point[count];
    for (std::size_t i = 0; i < count; ++i) {
        copy[i] = vertices[i];
    }
    delete[] vertices_;
    vertices_ = copy;
}

bool Figure::check_vertices(const Point* vertices) const {
    const std::size_t count = vertex_count();
    for (std::size_t i = 0; i < count; ++i) {
        if (!std::isfinite(vertices[i].x) || !std::isfinite(vertices[i].y)) {
            return false;
        }
        for (std::size_t j = i + 1; j < count; ++j) {
            const double distance = std::hypot(vertices[j].x - vertices[i].x, vertices[j].y - vertices[i].y);
            if (!std::isfinite(distance) || distance <= eps) {
                return false;
            }
        }
    }

    double area = 0.0;
    const Point origin = vertices[0];
    for (std::size_t i = 0; i < count; ++i) {
        const Point a = vertices[i];
        const Point b = vertices[(i + 1) % count];
        const Point c = vertices[(i + 2) % count];
        const double turn = orientation(a, b, c);
        if (!std::isfinite(turn) || std::abs(turn) <= eps) {
            return false;
        }
        area += (a.x - origin.x) * (b.y - origin.y) - (b.x - origin.x) * (a.y - origin.y);
        for (std::size_t j = i + 1; j < count; ++j) {
            if (j == i + 1 || (i == 0 && j == count - 1)) {
                continue;
            }
            if (intersects(a, b, vertices[j], vertices[(j + 1) % count])) {
                return false;
            }
        }
    }
    return std::isfinite(area) && area != 0.0;
}

Point Figure::vertex(std::size_t index) const {
    if (index >= vertex_count()) {
        std::cerr << "Ошибка: индекс вне границ фигуры\n";
        return Point{};
    }
    return vertices_ == nullptr ? Point{} : vertices_[index];
}

bool Figure::valid() const {
    return vertices_ != nullptr;
}

double Figure::metric() const {
    double area = 0.0;
    const Point origin = vertex(0);
    for (std::size_t i = 0; i < vertex_count(); ++i) {
        const Point a = vertex(i);
        const Point b = vertex((i + 1) % vertex_count());
        area += (a.x - origin.x) * (b.y - origin.y) - (b.x - origin.x) * (a.y - origin.y);
    }
    return std::abs(area) / 2.0;
}

double Figure::perimeter() const {
    double result = 0.0;
    for (std::size_t i = 0; i < vertex_count(); ++i) {
        const Point a = vertex(i);
        const Point b = vertex((i + 1) % vertex_count());
        result += std::hypot(b.x - a.x, b.y - a.y);
    }
    return result;
}

Point Figure::center() const {
    Point result;
    const double count = static_cast<double>(vertex_count());
    for (std::size_t i = 0; i < vertex_count(); ++i) {
        const Point point = vertex(i);
        result.x += point.x / count;
        result.y += point.y / count;
    }
    return result;
}

std::ostream& Figure::print(std::ostream& os) const {
    for (std::size_t i = 0; i < vertex_count(); ++i) {
        if (i != 0) {
            os << ' ';
        }
        const Point point = vertex(i);
        os << point.x << ' ' << point.y;
    }
    return os;
}

std::istream& Figure::read(std::istream& is) {
    const std::size_t count = vertex_count();
    Point* vertices = new Point[count];
    for (std::size_t i = 0; i < count; ++i) {
        if (!(is >> vertices[i].x >> vertices[i].y)) {
            delete[] vertices;
            return is;
        }
    }
    if (!check_vertices(vertices)) {
        delete[] vertices;
        is.setstate(std::ios::failbit);
        return is;
    }
    delete[] vertices_;
    vertices_ = vertices;
    return is;
}

Figure::operator double() const {
    return metric();
}

bool Figure::operator==(const Figure& other) const {
    return std::abs(metric() - other.metric()) < eps;
}

std::ostream& operator<<(std::ostream& os, const Figure& figure) {
    return figure.print(os);
}

std::istream& operator>>(std::istream& is, Figure& figure) {
    return figure.read(is);
}
