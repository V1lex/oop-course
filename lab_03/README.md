# Лабораторная работа №3

Вариант 18. Реализация упорядоченного множества IPv4-адресов с ручным управлением памятью на C++.

Поддерживаемые операции:

- создание, копирование и перемещение множества;
- присваивание через copy-and-swap;
- добавление и удаление адресов с проверкой октетов;
- проверка принадлежности, сравнение и вывод множеств;
- объединение, пересечение и разность;
- доступ к элементу по индексу только для чтения.

## Сборка

Команды выполняются из корня репозитория:

```bash
cmake -S lab_03 -B lab_03/build
cmake --build lab_03/build
```

## Запуск программы

```bash
./lab_03/build/lab03_main
```

## Запуск тестов

```bash
ctest --test-dir lab_03/build --output-on-failure
```

## Запуск с санитайзерами

Для Clang или GCC:

```bash
cmake -S lab_03 -B lab_03/build-asan -DCMAKE_CXX_FLAGS="-fsanitize=address,undefined -fno-omit-frame-pointer"
cmake --build lab_03/build-asan
ctest --test-dir lab_03/build-asan --output-on-failure
./lab_03/build-asan/lab03_main
```

Проект использует C++20, CMake и GoogleTest.
