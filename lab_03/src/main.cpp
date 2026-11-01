#include "IPAddressSet.h"

#include <iostream>
#include <limits>

void clear_input() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool read_int(const char* message, int& value) {
    std::cout << message;
    if (!(std::cin >> value)) {
        if (!std::cin.eof()) {
            clear_input();
            std::cout << "Ошибка: введите целое число\n";
        }
        return false;
    }
    clear_input();
    return true;
}

bool read_ip(IPAddress& ip) {
    std::cout << "Введите четыре октета через пробел: ";
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    if (!(std::cin >> a >> b >> c >> d)) {
        if (!std::cin.eof()) {
            clear_input();
            std::cout << "Ошибка: нужны четыре целых числа\n";
        }
        return false;
    }
    clear_input();
    if (a < 0 || a > 255 || b < 0 || b > 255 ||
        c < 0 || c > 255 || d < 0 || d > 255) {
        std::cout << "Ошибка: каждый октет должен быть от 0 до 255\n";
        return false;
    }
    ip = IPAddress(a, b, c, d);
    return true;
}

void print_menu() {
    std::cout << "\n1. Добавить IP\n"
              << "2. Удалить IP\n"
              << "3. Проверить наличие IP\n"
              << "4. Показать множества A и B\n"
              << "5. Объединение A | B\n"
              << "6. Пересечение A & B\n"
              << "7. Разность A - B\n"
              << "8. Показать IP по индексу\n"
              << "0. Выход\n";
}

int main() {
    IPAddressSet a;
    IPAddressSet b;

    while (!std::cin.eof()) {
        print_menu();
        int choice = 0;
        if (!read_int("Ваш выбор: ", choice)) {
            continue;
        }
        if (choice == 0) {
            return 0;
        }
        if (choice == 4) {
            std::cout << "A (" << a.size() << "): " << a << '\n'
                      << "B (" << b.size() << "): " << b << '\n';
        } else if (choice == 5) {
            std::cout << "A | B = " << (a | b) << '\n';
        } else if (choice == 6) {
            std::cout << "A & B = " << (a & b) << '\n';
        } else if (choice == 7) {
            std::cout << "A - B = " << (a - b) << '\n';
        } else if (choice == 1 || choice == 2 || choice == 3 || choice == 8) {
            int selected = 0;
            if (!read_int("Выберите множество (1 — A, 2 — B): ", selected)) {
                continue;
            }
            if (selected != 1 && selected != 2) {
                std::cout << "Ошибка: выберите 1 или 2\n";
                continue;
            }
            IPAddressSet& set = selected == 1 ? a : b;
            if (choice == 8) {
                int index = 0;
                if (!read_int("Индекс (от 0): ", index)) {
                    continue;
                }
                if (index < 0 || static_cast<std::size_t>(index) >= set.size()) {
                    std::cout << "Ошибка: индекс вне границ множества\n";
                } else {
                    std::cout << set[static_cast<std::size_t>(index)] << '\n';
                }
                continue;
            }
            IPAddress ip;
            if (!read_ip(ip)) {
                continue;
            }
            if (choice == 1) {
                std::cout << (set.add(ip) ? "IP добавлен\n" : "Такой IP уже есть\n");
            } else if (choice == 2) {
                std::cout << (set.remove(ip) ? "IP удалён\n" : "IP не найден\n");
            } else {
                std::cout << (set(ip) ? "IP есть в множестве\n" : "IP не найден\n");
            }
        } else {
            std::cout << "Ошибка: такого пункта меню нет\n";
        }
    }
}
