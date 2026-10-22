#include "my_string.h"

#include <utility>

String::String() : data_(new char[2]{}), size_(0), capacity_(1) {}

String::String(const char* str) : data_(nullptr), size_(0), capacity_(1) {
    if (str != nullptr) {
        while (str[size_] != '\0') {
            ++size_;
        }
    }

    if (size_ > capacity_) {
        capacity_ = size_;
    }

    data_ = new char[capacity_ + 1];

    for (std::size_t i = 0; i < size_; ++i) {
        data_[i] = str[i];
    }

    data_[size_] = '\0';
}

String::String(const String& other) : data_(nullptr), size_(other.size_), capacity_(other.capacity_) {
    if (capacity_ == 0) {
        capacity_ = 1;
    }

    data_ = new char[capacity_ + 1];

    for (std::size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }

    data_[size_] = '\0';
}

String::String(String&& other) : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

String& String::operator=(String other) {
    swap(other);
    return *this;
}

bool String::operator==(const char* str) const {
    if (str == nullptr) {
        return size_ == 0;
    }

    for (std::size_t i = 0; i < size_; ++i) {
        if (str[i] == '\0' || data_[i] != str[i]) {
            return false;
        }
    }

    return str[size_] == '\0';
}

String::~String() {
    delete[] data_;
}

void String::swap(String& other) {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

void String::reserve(std::size_t new_capacity) {
    if (new_capacity <= capacity_) {
        return;
    }

    std::size_t capacity = capacity_;

    if (capacity == 0) {
        capacity = 1;
    }

    while (capacity < new_capacity) {
        if (capacity > (npos - 1) / 2) {
            capacity = new_capacity;
            break;
        }

        capacity *= 2;
    }

    char* new_data = new char[capacity + 1];

    for (std::size_t i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
    }

    new_data[size_] = '\0';

    delete[] data_;

    data_ = new_data;
    capacity_ = capacity;
}

void String::push_back(char c) {
    if (size_ == npos - 1) {
        std::cerr << "Ошибка: превышен допустимый размер строки\n";
        return;
    }

    reserve(size_ + 1);

    data_[size_] = c;
    ++size_;
    data_[size_] = '\0';
}

void String::append(const String& other) {
    if (other.size_ == 0) {
        return;
    }

    if (other.size_ > npos - 1 - size_) {
        std::cerr << "Ошибка: превышен допустимый размер строки\n";
        return;
    }

    std::size_t append_size = other.size_;

    reserve(size_ + append_size);

    for (std::size_t i = 0; i < append_size; ++i) {
        data_[size_ + i] = other.data_[i];
    }

    size_ += append_size;
    data_[size_] = '\0';
}

std::size_t String::find(const String& substr) const {
    if (substr.size_ > size_) {
        return npos;
    }

    for (std::size_t i = 0; i <= size_ - substr.size_; ++i) {
        std::size_t j = 0;

        while (j < substr.size_ && data_[i + j] == substr.data_[j]) {
            ++j;
        }

        if (j == substr.size_) {
            return i;
        }
    }

    return npos;
}

void String::print(std::ostream& out) const {
    for (std::size_t i = 0; i < size_; ++i) {
        out.put(data_[i]);
    }
}

String String::remove_char(char c) const {
    String result(*this);
    std::size_t position = 0;

    for (std::size_t i = 0; i < result.size_; ++i) {
        if (result.data_[i] != c) {
            result.data_[position] = result.data_[i];
            ++position;
        }
    }

    result.size_ = position;
    result.data_[position] = '\0';

    return result;
}
