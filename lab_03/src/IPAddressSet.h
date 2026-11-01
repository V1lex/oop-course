#pragma once

#include <iostream>
#include <cstddef>

#include "IPAddress.h"

class IPAddressSet {
public:
    IPAddressSet();
    IPAddressSet(const IPAddressSet& other);
    IPAddressSet(IPAddressSet&& other) noexcept;

    IPAddressSet& operator=(const IPAddressSet& other);
    IPAddressSet& operator=(IPAddressSet&& other) noexcept;

    ~IPAddressSet();

    bool add(const IPAddress& ip);
    bool remove(const IPAddress& ip);
    bool contains(const IPAddress& ip) const;

    bool operator()(const IPAddress& ip) const;

    std::size_t size() const;
    bool empty() const;

    IPAddressSet& operator+=(const IPAddress& ip);
    IPAddressSet& operator-=(const IPAddress& ip);

    IPAddressSet operator|(const IPAddressSet& other) const;
    IPAddressSet operator&(const IPAddressSet& other) const;
    IPAddressSet operator-(const IPAddressSet& other) const;

    bool operator==(const IPAddressSet& other) const;
    bool operator!=(const IPAddressSet& other) const;

    IPAddress operator[](std::size_t index) const;

    friend std::ostream& operator<<(std::ostream& os, const IPAddressSet& set);

private:
    void swap(IPAddressSet& other) noexcept;
    std::size_t lower_bound(const IPAddress& ip) const;
    void increase_capacity();
    void decrease_capacity();
    bool append_sorted(const IPAddress& ip);

    IPAddress* data_;
    std::size_t size_;
    std::size_t capacity_;
};
