#include "IPAddressSet.h"

#include <limits>
#include <utility>

IPAddressSet::IPAddressSet() : data_(nullptr), size_(0), capacity_(0) {}

IPAddressSet::IPAddressSet(const IPAddressSet& other)
    : data_(other.size_ == 0 ? nullptr : new IPAddress[other.size_]),
      size_(other.size_), capacity_(other.size_) {
    for (std::size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
}

IPAddressSet::IPAddressSet(IPAddressSet&& other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

IPAddressSet& IPAddressSet::operator=(const IPAddressSet& other) {
    if (this != &other) {
        IPAddressSet copy(other);
        swap(copy);
    }
    return *this;
}

IPAddressSet& IPAddressSet::operator=(IPAddressSet&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

IPAddressSet::~IPAddressSet() {
    delete[] data_;
}

void IPAddressSet::swap(IPAddressSet& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

std::size_t IPAddressSet::lower_bound(const IPAddress& ip) const {
    std::size_t left = 0;
    std::size_t right = size_;
    while (left < right) {
        const std::size_t middle = left + (right - left) / 2;
        if (data_[middle] < ip) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    return left;
}

void IPAddressSet::increase_capacity() {
    if (size_ < capacity_) {
        return;
    }

    const std::size_t max_capacity = std::numeric_limits<std::size_t>::max() / sizeof(IPAddress);
    if (capacity_ == max_capacity) {
        std::cerr << "Ошибка: превышен допустимый размер множества\n";
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

    IPAddress* new_data = new IPAddress[new_capacity];
    for (std::size_t i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
}

void IPAddressSet::decrease_capacity() {
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
    IPAddress* new_data = new IPAddress[new_capacity];

    for (std::size_t i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
    }

    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
}

bool IPAddressSet::append_sorted(const IPAddress& ip) {
    increase_capacity();
    if (size_ == capacity_) {
        return false;
    }

    data_[size_] = ip;
    ++size_;
    return true;
}

bool IPAddressSet::add(const IPAddress& ip) {
    if (!ip.valid()) {
        return false;
    }

    const std::size_t position = lower_bound(ip);
    if (position < size_ && data_[position] == ip) {
        return false;
    }

    increase_capacity();
    if (size_ == capacity_) {
        return false;
    }

    for (std::size_t i = size_; i > position; --i) {
        data_[i] = data_[i - 1];
    }
    data_[position] = ip;
    ++size_;
    return true;
}

bool IPAddressSet::remove(const IPAddress& ip) {
    const std::size_t position = lower_bound(ip);
    if (position == size_ || !(data_[position] == ip)) {
        return false;
    }
    for (std::size_t i = position + 1; i < size_; ++i) {
        data_[i - 1] = data_[i];
    }
    --size_;
    decrease_capacity();
    return true;
}

bool IPAddressSet::contains(const IPAddress& ip) const {
    const std::size_t position = lower_bound(ip);
    return position < size_ && data_[position] == ip;
}

bool IPAddressSet::operator()(const IPAddress& ip) const {
    return contains(ip);
}

std::size_t IPAddressSet::size() const {
    return size_;
}

bool IPAddressSet::empty() const {
    return size_ == 0;
}

IPAddressSet& IPAddressSet::operator+=(const IPAddress& ip) {
    add(ip);
    return *this;
}

IPAddressSet& IPAddressSet::operator-=(const IPAddress& ip) {
    remove(ip);
    return *this;
}

IPAddressSet IPAddressSet::operator|(const IPAddressSet& other) const {
    IPAddressSet result;
    std::size_t i = 0;
    std::size_t j = 0;
    while (i < size_ && j < other.size_) {
        if (data_[i] < other.data_[j]) {
            if (!result.append_sorted(data_[i++])) {
                return IPAddressSet();
            }
        } else if (other.data_[j] < data_[i]) {
            if (!result.append_sorted(other.data_[j++])) {
                return IPAddressSet();
            }
        } else {
            if (!result.append_sorted(data_[i++])) {
                return IPAddressSet();
            }
            ++j;
        }
    }
    while (i < size_) {
        if (!result.append_sorted(data_[i++])) {
            return IPAddressSet();
        }
    }
    while (j < other.size_) {
        if (!result.append_sorted(other.data_[j++])) {
            return IPAddressSet();
        }
    }
    return result;
}

IPAddressSet IPAddressSet::operator&(const IPAddressSet& other) const {
    IPAddressSet result;
    std::size_t i = 0;
    std::size_t j = 0;
    while (i < size_ && j < other.size_) {
        if (data_[i] < other.data_[j]) {
            ++i;
        } else if (other.data_[j] < data_[i]) {
            ++j;
        } else {
            if (!result.append_sorted(data_[i++])) {
                return IPAddressSet();
            }
            ++j;
        }
    }
    return result;
}

IPAddressSet IPAddressSet::operator-(const IPAddressSet& other) const {
    IPAddressSet result;
    std::size_t i = 0;
    std::size_t j = 0;
    while (i < size_ && j < other.size_) {
        if (data_[i] < other.data_[j]) {
            if (!result.append_sorted(data_[i++])) {
                return IPAddressSet();
            }
        } else if (other.data_[j] < data_[i]) {
            ++j;
        } else {
            ++i;
            ++j;
        }
    }
    while (i < size_) {
        if (!result.append_sorted(data_[i++])) {
            return IPAddressSet();
        }
    }
    return result;
}

bool IPAddressSet::operator==(const IPAddressSet& other) const {
    if (size_ != other.size_) {
        return false;
    }
    for (std::size_t i = 0; i < size_; ++i) {
        if (!(data_[i] == other.data_[i])) {
            return false;
        }
    }
    return true;
}

bool IPAddressSet::operator!=(const IPAddressSet& other) const {
    return !(*this == other);
}

IPAddress IPAddressSet::operator[](std::size_t index) const {
    if (index >= size_) {
        std::cerr << "Ошибка: индекс вне границ множества\n";
        return IPAddress(-1, -1, -1, -1);
    }
    return data_[index];
}

std::ostream& operator<<(std::ostream& os, const IPAddressSet& set) {
    os << "{ ";
    for (std::size_t i = 0; i < set.size_; ++i) {
        if (i != 0) {
            os << ", ";
        }
        os << set.data_[i];
    }
    if (!set.empty()) {
        os << ' ';
    }
    return os << '}';
}
