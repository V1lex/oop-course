#pragma once

#include <cstddef>
#include <iostream>
#include <limits>

class String {
public:
    static constexpr std::size_t npos = std::numeric_limits<std::size_t>::max();

    String();
    String(const char* str);
    String(const String& other);
    String(String&& other);
    String& operator=(String other);
    bool operator==(const char* str) const;
    ~String();

    void push_back(char c);
    void append(const String& other);
    std::size_t find(const String& substr) const;
    void print(std::ostream& out) const;

    String remove_char(char c) const;

private:
    void swap(String& other);
    void reserve(std::size_t new_capacity);

    char* data_;
    std::size_t size_;
    std::size_t capacity_;
};
