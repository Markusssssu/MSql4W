# My Sqlite For Work Программа для работы с базой данных SQLite 

Это программа на C++ для работы с базой данных SQLite. Она позволяет создавать таблицы, вставлять, обновлять, удалять и выбирать данные, а также выполнять произвольные SQL-запросы. Данные сохраняются в локальном файле `database.db`. 

Основаная цель программы, помочь студентам колледжа, и других учебных заведений в легком и доступном использовании баз данных

## Возможности

- Создание таблиц с указанием количества столбцов, их имён и типов данных.
- Вставка, обновление, удаление и выборка данных.
- Ручной ввод SQL-запросов (например, `JOIN`, `DISTINCT`, `GROUP BY` и т.д.).
- Сохранение данных между запусками программы.
- Qt оптимальные версии

## Установка

### Требования

- Компилятор C++ (например, `g++`).
- Библиотека SQLite3.

### Инструкция

1. Убедись, что у тебя установлен `g++` и SQLite3.
   - На Windows установи [MinGW](http://www.mingw.org/) или [MSYS2](https://www.msys2.org/).
   - На Linux используй пакетный менеджер (например, `sudo apt install g++ sqlite3`).
2. Пакетный менеджер для дистрибувов.
   - Arch (`sudo pacman -S g++` `sudo pacman -S sqlite3`)
   - Fedora (`sudo dnf install g++ sqlite3`)
   - Debian (`sudo apt install g++ sqlite3`)
3. Склонируй репозиторий:
   ```bash
   git clone https://github.com/Markusssssu/MSql4W.git
   cd MSql4W\Sqlite3\x64\Debug
4. Запустить программу:
  ```bash
    .\sqlite3                                       

