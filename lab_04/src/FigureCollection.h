#pragma once

#include "Figure.h"

#include <cstddef>

class FigureCollection {
public:
    FigureCollection();
    FigureCollection(const FigureCollection& other);
    FigureCollection(FigureCollection&& other) noexcept;
    FigureCollection& operator=(const FigureCollection& other);
    FigureCollection& operator=(FigureCollection&& other) noexcept;
    ~FigureCollection();

    void swap(FigureCollection& other) noexcept;
    bool add(const Figure& figure);
    bool remove(std::size_t index);
    void clear() noexcept;
    std::size_t size() const;
    bool empty() const;
    double total_metric() const;
    Figure* operator[](std::size_t index);
    const Figure* operator[](std::size_t index) const;

private:
    void increase_capacity();
    void decrease_capacity();

    Figure** data_;
    std::size_t size_;
    std::size_t capacity_;
};
