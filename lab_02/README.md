# Лабораторная работа №2

Вариант 2. Реализация класса `String` с ручным управлением памятью на C++.

Поддерживаемые операции:

- создание, копирование и перемещение строки;
- присваивание через copy-and-swap;
- сравнение с C-строкой через `==`;
- добавление символа и строки в конец;
- поиск подстроки и вывод строки;
- удаление всех вхождений заданного символа в новой строке.

## Сборка

Команды выполняются из корня репозитория:

```bash
cmake -S lab_02 -B lab_02/build
cmake --build lab_02/build
```

## Запуск программы

```bash
./lab_02/build/lab02_main
```

## Запуск тестов

```bash
ctest --test-dir lab_02/build --output-on-failure
```

## Запуск с санитайзерами

Для Clang или GCC:

```bash
cmake -S lab_02 -B lab_02/build-asan -DCMAKE_CXX_FLAGS="-fsanitize=address,undefined -fno-omit-frame-pointer"
cmake --build lab_02/build-asan
ctest --test-dir lab_02/build-asan --output-on-failure
./lab_02/build-asan/lab02_main
```

Проект использует C++20, CMake и GoogleTest.
