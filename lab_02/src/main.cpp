#include "my_string.h"

#include <iostream>
#include <limits>
#include <utility>

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

bool read_line(const char* message, String& value) {
    std::cout << message;

    String result;
    char c = '\0';
    bool has_input = false;

    while (std::cin.get(c)) {
        has_input = true;

        if (c == '\n') {
            value = std::move(result);
            return true;
        }

        result.push_back(c);
    }

    if (std::cin.eof() && has_input) {
        value = std::move(result);
        return true;
    }

    return false;
}

bool read_char(const char* message, char& value) {
    std::cout << message;

    char c = '\0';

    if (!std::cin.get(c)) {
        return false;
    }

    if (c == '\n') {
        std::cout << "Ошибка: введите ровно один символ\n";
        return false;
    }

    char next = '\0';

    if (std::cin.get(next)) {
        if (next != '\n') {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка: введите ровно один символ\n";
            return false;
        }
    } else if (!std::cin.eof()) {
        return false;
    }

    value = c;
    return true;
}

void print_menu() {
    std::cout << '\n';
    std::cout << "1. Создать строку\n";
    std::cout << "2. Напечатать строку\n";
    std::cout << "3. Добавить строку в конец\n";
    std::cout << "4. Добавить символ в конец\n";
    std::cout << "5. Найти подстроку\n";
    std::cout << "6. Удалить все вхождения символа\n";
    std::cout << "0. Выход\n";
}

int main() {
    String str;

    while (true) {
        print_menu();

        int choice = 0;

        if (!read_int("Ваш выбор: ", choice)) {
            if (std::cin.eof()) {
                return 0;
            }

            continue;
        }

        if (choice == 0) {
            return 0;
        }

        if (choice == 1) {
            if (!read_line("Введите строку: ", str)) {
                return 0;
            }

            std::cout << "Строка создана\n";
            str.print(std::cout);
            std::cout << '\n';
        } else if (choice == 2) {
            str.print(std::cout);
            std::cout << '\n';
        } else if (choice == 3) {
            String suffix;

            if (!read_line("Введите добавляемую строку: ", suffix)) {
                return 0;
            }

            str.append(suffix);

            std::cout << "Строка дополнена\n";
            str.print(std::cout);
            std::cout << '\n';
        } else if (choice == 4) {
            char c = '\0';

            if (!read_char("Введите символ: ", c)) {
                if (std::cin.eof()) {
                    return 0;
                }

                continue;
            }

            str.push_back(c);

            std::cout << "Символ добавлен\n";
            str.print(std::cout);
            std::cout << '\n';
        } else if (choice == 5) {
            String substr;

            if (!read_line("Введите искомую подстроку: ", substr)) {
                return 0;
            }

            std::size_t position = str.find(substr);

            if (position == String::npos) {
                std::cout << "Подстрока не найдена\n";
            } else {
                std::cout << "Позиция первого вхождения: " << position << '\n';
            }
        } else if (choice == 6) {
            char c = '\0';

            if (!read_char("Введите удаляемый символ: ", c)) {
                if (std::cin.eof()) {
                    return 0;
                }

                continue;
            }

            str = str.remove_char(c);

            std::cout << "Результат: ";
            str.print(std::cout);
            std::cout << '\n';
        } else {
            std::cout << "Ошибка: такого пункта меню нет\n";
        }
    }
}
