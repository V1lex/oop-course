#include "array_ops.h"

#include <iostream>

void clear_input() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

bool read_int(const char* message, int& value) {
    std::cout << message;

    if (!(std::cin >> value)) {
        clear_input();
        std::cout << "Ошибка: введите целое число\n";
        return false;
    }

    return true;
}

void print_menu() {
    std::cout << '\n';
    std::cout << "1. Создать массив\n";
    std::cout << "2. Удалить массив\n";
    std::cout << "3. Напечатать массив\n";
    std::cout << "4. Вставить элемент\n";
    std::cout << "5. Удалить элемент\n";
    std::cout << "6. Изменить размер\n";
    std::cout << "7. Подсчитать элементы в диапазоне\n";
    std::cout << "8. Сортировать подсчётом\n";
    std::cout << "0. Выход\n";
}

int main() {
    int* arr = nullptr;
    std::size_t size = 0;

    while (true) {
        print_menu();

        int choice = 0;

        if (!read_int("Ваш выбор: ", choice)) {
            continue;
        }

        if (choice == 0) {
            array_delete(arr);
            return 0;
        }

        if (choice == 1) {
            int input_size = 0;

            if (!read_int("Введите размер массива: ", input_size)) {
                continue;
            }

            if (input_size < 0) {
                std::cout << "Ошибка: размер не может быть отрицательным\n";
                continue;
            }

            array_delete(arr);

            size = static_cast<std::size_t>(input_size);
            arr = array_create(size);

            for (std::size_t i = 0; i < size; ++i) {
                while (true) {
                    std::cout << "Введите элемент [" << i << "] от 0 до 1023: ";

                    int value = 0;

                    if (!read_int("", value)) {
                        continue;
                    }

                    if (value < 0 || value > 1023) {
                        std::cout << "Ошибка: число должно быть от 0 до 1023\n";
                        continue;
                    }

                    arr[i] = value;
                    break;
                }
            }

            std::cout << "Массив создан\n";
            array_print(arr, size);
        } else if (choice == 2) {
            if (size == 0) {
                std::cout << "Массив уже пустой\n";
                continue;
            }

            array_delete(arr);
            size = 0;

            std::cout << "Массив удалён\n";
        } else if (choice == 3) {
            array_print(arr, size);
        } else if (choice == 4) {
            int input_pos = 0;

            if (!read_int("Введите позицию вставки: ", input_pos)) {
                continue;
            }

            if (input_pos < 0 || static_cast<std::size_t>(input_pos) > size) {
                std::cout << "Ошибка: неправильная позиция\n";
                continue;
            }

            int value = 0;

            if (!read_int("Введите значение от 0 до 1023: ", value)) {
                continue;
            }

            if (value < 0 || value > 1023) {
                std::cout << "Ошибка: число должно быть от 0 до 1023\n";
                continue;
            }

            std::size_t pos = static_cast<std::size_t>(input_pos);

            arr = array_insert(arr, size, pos, value);

            std::cout << "Элемент вставлен\n";
            array_print(arr, size);
        } else if (choice == 5) {
            if (size == 0) {
                std::cout << "Массив пустой\n";
                continue;
            }

            int input_pos = 0;

            if (!read_int("Введите позицию удаления: ", input_pos)) {
                continue;
            }

            if (input_pos < 0 || static_cast<std::size_t>(input_pos) >= size) {
                std::cout << "Ошибка: неправильная позиция\n";
                continue;
            }

            std::size_t pos = static_cast<std::size_t>(input_pos);

            arr = array_remove(arr, size, pos);

            std::cout << "Элемент удалён\n";
            array_print(arr, size);
        } else if (choice == 6) {
            int input_size = 0;

            if (!read_int("Введите новый размер: ", input_size)) {
                continue;
            }

            if (input_size < 0) {
                std::cout << "Ошибка: размер не может быть отрицательным\n";
                continue;
            }

            std::size_t new_size = static_cast<std::size_t>(input_size);

            arr = array_resize(arr, size, new_size);
            size = new_size;

            std::cout << "Размер изменён\n";
            array_print(arr, size);
        } else if (choice == 7) {
            int lo = 0;
            int hi = 0;

            if (!read_int("Введите нижнюю границу от 0 до 1023: ", lo)) {
                continue;
            }

            if (lo < 0 || lo > 1023) {
                std::cout << "Ошибка: число должно быть от 0 до 1023\n";
                continue;
            }

            if (!read_int("Введите верхнюю границу от 0 до 1023: ", hi)) {
                continue;
            }

            if (hi < 0 || hi > 1023) {
                std::cout << "Ошибка: число должно быть от 0 до 1023\n";
                continue;
            }

            if (lo > hi) {
                std::cout << "Ошибка: нижняя граница больше верхней\n";
                continue;
            }

            std::size_t result = array_range_count(arr, size, lo, hi);

            std::cout << "Количество элементов в диапазоне: " << result << '\n';
        } else if (choice == 8) {
            if (size == 0) {
                std::cout << "Массив пустой\n";
                continue;
            }

            array_counting_sort(arr, size);

            std::cout << "Отсортированный массив:\n";
            array_print(arr, size);
        } else {
            std::cout << "Ошибка: такого пункта меню нет\n";
        }
    }
}