#include "FigureCollection.h"
#include "Pentagon.h"
#include "Square.h"
#include "Triangle.h"

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

bool read_index(const FigureCollection& figures, std::size_t& index) {
    int value = 0;
    if (!read_int("Индекс фигуры (от 0): ", value)) {
        return false;
    }
    if (value < 0 || static_cast<std::size_t>(value) >= figures.size()) {
        std::cout << "Ошибка: индекс вне границ коллекции\n";
        return false;
    }
    index = static_cast<std::size_t>(value);
    return true;
}

void read_and_add(FigureCollection& figures, Figure& figure) {
    std::cout << "Введите " << figure.vertex_count() << " пар координат x y в порядке обхода: ";
    if (!(std::cin >> figure)) {
        if (!std::cin.eof()) {
            clear_input();
            std::cout << "Ошибка: неверные координаты или форма " << figure.name() << '\n';
        }
        return;
    }
    clear_input();
    if (figures.add(figure)) {
        std::cout << "Фигура добавлена\n";
    }
}

void add_figure(FigureCollection& figures) {
    int type = 0;
    if (!read_int("Тип (1 — Triangle, 2 — Square, 3 — Pentagon): ", type)) {
        return;
    }
    if (type == 1) {
        Triangle triangle;
        read_and_add(figures, triangle);
    } else if (type == 2) {
        Square square;
        read_and_add(figures, square);
    } else if (type == 3) {
        Pentagon pentagon;
        read_and_add(figures, pentagon);
    } else {
        std::cout << "Ошибка: выберите тип от 1 до 3\n";
    }
}

void print_figure(const Figure& figure) {
    const Point middle = figure.center();
    std::cout << figure.name() << ": " << figure << '\n'
              << "Центр: (" << middle.x << ", " << middle.y << ")\n"
              << "Площадь: " << static_cast<double>(figure) << '\n';
}

void print_details(const Figure& figure) {
    print_figure(figure);
    std::cout << "Периметр: " << figure.perimeter() << '\n';
    if (const auto* triangle = dynamic_cast<const Triangle*>(&figure)) {
        std::cout << "Равносторонний: " << (triangle->isEquilateral() ? "да" : "нет") << '\n';
    } else if (const auto* square = dynamic_cast<const Square*>(&figure)) {
        std::cout << "Сторона: " << square->side() << '\n';
    } else if (const auto* pentagon = dynamic_cast<const Pentagon*>(&figure)) {
        std::cout << "Правильный: " << (pentagon->isRegular() ? "да" : "нет") << '\n';
    }
}

void print_type_counts(const FigureCollection& figures) {
    std::size_t triangles = 0;
    std::size_t squares = 0;
    std::size_t pentagons = 0;
    for (std::size_t i = 0; i < figures.size(); ++i) {
        const Figure* figure = figures[i];
        if (dynamic_cast<const Triangle*>(figure)) {
            ++triangles;
        } else if (dynamic_cast<const Square*>(figure)) {
            ++squares;
        } else if (dynamic_cast<const Pentagon*>(figure)) {
            ++pentagons;
        }
    }
    std::cout << "Треугольников: " << triangles << '\n';
    std::cout << "Квадратов: " << squares << '\n';
    std::cout << "Пятиугольников: " << pentagons << '\n';
}

void compare_figures(const Figure& first, const Figure& second) {
    std::cout << "Первая фигура:\n";
    print_figure(first);
    std::cout << "Вторая фигура:\n";
    print_figure(second);
    if (first == second) {
        std::cout << "Площади равны" << '\n';
    } else if (first.metric() > second.metric()) {
        std::cout << "Площадь первой фигуры больше на " << first.metric() - second.metric() << '\n';
    } else {
        std::cout << "Площадь второй фигуры больше на " << second.metric() - first.metric() << '\n';
    }
}

void print_menu() {
    std::cout << "\n1. Добавить фигуру\n"
              << "2. Удалить фигуру\n"
              << "3. Показать все фигуры\n"
              << "4. Суммарная площадь\n"
              << "5. Периметр и свойства фигуры\n"
              << "6. Сравнить площади двух фигур\n"
              << "7. Очистить коллекцию\n"
              << "8. Количество фигур каждого типа\n"
              << "0. Выход\n";
}

int main() {
    FigureCollection figures;

    while (!std::cin.eof()) {
        print_menu();
        int choice = 0;
        if (!read_int("Ваш выбор: ", choice)) {
            continue;
        }
        if (choice == 0) {
            return 0;
        }
        if (choice == 1) {
            add_figure(figures);
        } else if (choice == 2 || choice == 5) {
            std::size_t index = 0;
            if (!read_index(figures, index)) {
                continue;
            }
            if (choice == 2) {
                figures.remove(index);
                std::cout << "Фигура удалена\n";
            } else {
                print_details(*figures[index]);
            }
        } else if (choice == 3) {
            std::cout << "Фигур: " << figures.size() << '\n';
            for (std::size_t i = 0; i < figures.size(); ++i) {
                std::cout << i << ". ";
                print_figure(*figures[i]);
            }
        } else if (choice == 4) {
            std::cout << "Суммарная площадь: " << figures.total_metric() << '\n';
        } else if (choice == 6) {
            std::size_t first = 0;
            std::size_t second = 0;
            if (read_index(figures, first) && read_index(figures, second)) {
                compare_figures(*figures[first], *figures[second]);
            }
        } else if (choice == 7) {
            figures.clear();
            std::cout << "Коллекция очищена\n";
        } else if (choice == 8) {
            print_type_counts(figures);
        } else {
            std::cout << "Ошибка: такого пункта меню нет\n";
        }
    }
}
