#include "FigureCollection.h"

#include <limits>
#include <utility>

FigureCollection::FigureCollection() : data_(nullptr), size_(0), capacity_(0) {}

FigureCollection::FigureCollection(const FigureCollection& other) : FigureCollection() {
    FigureCollection copy;
    if (other.size_ != 0) {
        copy.data_ = new Figure*[other.size_];
        copy.capacity_ = other.size_;
        for (std::size_t i = 0; i < other.size_; ++i) {
            copy.data_[i] = other.data_[i]->clone();
            ++copy.size_;
        }
    }
    swap(copy);
}

FigureCollection::FigureCollection(FigureCollection&& other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

FigureCollection& FigureCollection::operator=(const FigureCollection& other) {
    if (this != &other) {
        FigureCollection copy(other);
        swap(copy);
    }
    return *this;
}

FigureCollection& FigureCollection::operator=(FigureCollection&& other) noexcept {
    if (this != &other) {
        clear();
        swap(other);
    }
    return *this;
}

FigureCollection::~FigureCollection() {
    clear();
}

void FigureCollection::swap(FigureCollection& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

void FigureCollection::increase_capacity() {
    if (size_ < capacity_) {
        return;
    }
    const std::size_t max_capacity = std::numeric_limits<std::size_t>::max() / sizeof(Figure*);
    if (capacity_ == max_capacity) {
        std::cerr << "Ошибка: превышен допустимый размер коллекции\n";
        return;
    }
    std::size_t new_capacity;
    if (capacity_ == 0) {
        new_capacity = 1;
    } else if (capacity_ > max_capacity / 2) {
        new_capacity = max_capacity;
    } else {
        new_capacity = capacity_ * 2;
    }
    Figure** new_data = new Figure*[new_capacity];
    for (std::size_t i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
}

void FigureCollection::decrease_capacity() {
    if (size_ == 0) {
        delete[] data_;
        data_ = nullptr;
        capacity_ = 0;
        return;
    }
    if (size_ > capacity_ / 4) {
        return;
    }
    const std::size_t new_capacity = capacity_ / 2;
    Figure** new_data = new Figure*[new_capacity];
    for (std::size_t i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
}

bool FigureCollection::add(const Figure& figure) {
    if (!figure.valid()) {
        return false;
    }
    increase_capacity();
    if (size_ == capacity_) {
        return false;
    }
    data_[size_] = figure.clone();
    ++size_;
    return true;
}

bool FigureCollection::remove(std::size_t index) {
    if (index >= size_) {
        return false;
    }
    delete data_[index];
    for (std::size_t i = index + 1; i < size_; ++i) {
        data_[i - 1] = data_[i];
    }
    --size_;
    decrease_capacity();
    return true;
}

void FigureCollection::clear() noexcept {
    for (std::size_t i = 0; i < size_; ++i) {
        delete data_[i];
    }
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

std::size_t FigureCollection::size() const {
    return size_;
}

bool FigureCollection::empty() const {
    return size_ == 0;
}

double FigureCollection::total_metric() const {
    double result = 0.0;
    for (std::size_t i = 0; i < size_; ++i) {
        result += data_[i]->metric();
    }
    return result;
}

Figure* FigureCollection::operator[](std::size_t index) {
    if (index >= size_) {
        std::cerr << "Ошибка: индекс вне границ коллекции\n";
        return nullptr;
    }
    return data_[index];
}

const Figure* FigureCollection::operator[](std::size_t index) const {
    if (index >= size_) {
        std::cerr << "Ошибка: индекс вне границ коллекции\n";
        return nullptr;
    }
    return data_[index];
}
