#include "array_ops.h"

#include <iostream>

int* array_create(std::size_t size) {
    if (size == 0) {
        return nullptr;
    }

    return new int[size]{};
}

void array_delete(int*& arr) {
    delete[] arr;
    arr = nullptr;
}

int* array_resize(int* arr, std::size_t size, std::size_t new_size) {
    if (new_size == size) {
        return arr;
    }

    if (new_size == 0) {
        delete[] arr;
        return nullptr;
    }

    int* new_arr = new int[new_size]{};

    std::size_t copy_size = 0;

    if (size < new_size) {
        copy_size = size;
    } else {
        copy_size = new_size;
    }

    for (std::size_t i = 0; i < copy_size; ++i) {
        new_arr[i] = arr[i];
    }

    delete[] arr;

    return new_arr;
}

int* array_insert(int* arr, std::size_t& size, std::size_t pos, int value) {
    if (pos > size) {
        return arr;
    }

    int* new_arr = new int[size + 1]{};

    for (std::size_t i = 0; i < pos; ++i) {
        new_arr[i] = arr[i];
    }

    new_arr[pos] = value;

    for (std::size_t i = pos; i < size; ++i) {
        new_arr[i + 1] = arr[i];
    }

    delete[] arr;

    ++size;

    return new_arr;
}

int* array_remove(int* arr, std::size_t& size, std::size_t pos) {
    if (pos >= size) {
        return arr;
    }

    std::size_t new_size = size - 1;
    int* new_arr = nullptr;

    if (new_size > 0) {
        new_arr = new int[new_size]{};

        for (std::size_t i = 0; i < pos; ++i) {
            new_arr[i] = arr[i];
        }

        for (std::size_t i = pos; i < new_size; ++i) {
            new_arr[i] = arr[i + 1];
        }
    }

    delete[] arr;

    size = new_size;

    return new_arr;
}

void array_print(const int* arr, std::size_t size) {
    if (arr == nullptr || size == 0) {
        std::cout << "Массив пустой" << '\n';
        return;
    }

    for (std::size_t i = 0; i < size; ++i) {
        std::cout << arr[i];

        if (i + 1 < size) {
            std::cout << ' ';
        }
    }

    std::cout << '\n';
}

void array_counting_sort(int* arr, std::size_t size) {
    if (arr == nullptr || size == 0) {
        return;
    }

    for (std::size_t i = 0; i < size; ++i) {
        if (arr[i] < 0 || arr[i] > 1023) {
            return;
        }
    }

    std::size_t count[1024] = {};

    for (std::size_t i = 0; i < size; ++i) {
        ++count[arr[i]];
    }

    std::size_t position = 0;

    for (std::size_t value = 0; value < 1024; ++value) {
        while (count[value] > 0) {
            arr[position] = static_cast<int>(value);
            ++position;
            --count[value];
        }
    }
}

std::size_t array_range_count(const int* arr, std::size_t size, int lo, int hi) {
    if (arr == nullptr || size == 0 || lo > hi) {
        return 0;
    }

    if (hi < 0 || lo > 1023) {
        return 0;
    }

    if (lo < 0) {
        lo = 0;
    }

    if (hi > 1023) {
        hi = 1023;
    }

    std::size_t count[1024] = {};

    for (std::size_t i = 0; i < size; ++i) {
        if (arr[i] < 0 || arr[i] > 1023) {
            return 0;
        }

        ++count[arr[i]];
    }

    for (std::size_t i = 1; i < 1024; ++i) {
        count[i] += count[i - 1];
    }

    if (lo == 0) {
        return count[hi];
    }

    return count[hi] - count[lo - 1];
}
