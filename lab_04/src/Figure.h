#pragma once

#include "Point.h"

#include <cstddef>
#include <iostream>

class Figure {
public:
    static constexpr double eps = 1e-6;

    virtual ~Figure();

    virtual const char* name() const = 0;
    virtual std::size_t vertex_count() const = 0;
    virtual Figure* clone() const = 0;
    virtual double metric() const;
    virtual double perimeter() const;
    virtual Point center() const;
    virtual std::ostream& print(std::ostream& os) const;
    virtual std::istream& read(std::istream& is);

    Point vertex(std::size_t index) const;
    bool valid() const;
    explicit operator double() const;
    bool operator==(const Figure& other) const;

protected:
    Figure();
    void set_vertices(const Point* vertices, std::size_t count);
    virtual bool check_vertices(const Point* vertices) const;
    Figure(const Figure& other);
    Figure(Figure&& other) noexcept;
    Figure& operator=(const Figure& other);
    Figure& operator=(Figure&& other) noexcept;

private:
    Point* vertices_;
};

std::ostream& operator<<(std::ostream& os, const Figure& figure);
std::istream& operator>>(std::istream& is, Figure& figure);
