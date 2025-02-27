#include <sqlite3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

void executeSQL(sqlite3* db, const std::string& sql) {
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка SQL: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void printTable(sqlite3_stmt* stmt) {
    int columnCount = sqlite3_column_count(stmt);

    std::vector<int>* columnWidths = new std::vector<int>(columnCount, 0);
    for (int i = 0; i < columnCount; ++i) {
        (*columnWidths)[i] = std::string(sqlite3_column_name(stmt, i)).length();
    }

    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        for (int i = 0; i < columnCount; ++i) {
            const char* value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
            if (value) {
                int length = std::string(value).length();
                if (length > (*columnWidths)[i]) {
                    (*columnWidths)[i] = length;
                }
            }
        }
    }
    sqlite3_reset(stmt); 

    
    std::cout << "+";
    for (int width : *columnWidths) {
        std::cout << std::string(width + 2, '-') << "+";
    }
    std::cout << "\n";

    
    std::cout << "|";
    for (int i = 0; i < columnCount; ++i) {
        std::cout << " " << std::setw((*columnWidths)[i]) << std::left << sqlite3_column_name(stmt, i) << " |";
    }
    std::cout << "\n";

    
    std::cout << "+";
    for (int width : *columnWidths) {
        std::cout << std::string(width + 2, '-') << "+";
    }
    std::cout << "\n";

    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::cout << "|";
        for (int i = 0; i < columnCount; ++i) {
            const char* value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
            std::cout << " " << std::setw((*columnWidths)[i]) << std::left << (value ? value : "NULL") << " |";
        }
        std::cout << "\n";
    }

   
    std::cout << "+";
    for (int width : *columnWidths) {
        std::cout << std::string(width + 2, '-') << "+";
    }
    std::cout << "\n";

    delete columnWidths; 
}

void executeQuery(sqlite3* db, const std::string& sql) {
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc == SQLITE_OK) {
        printTable(stmt);
    }
    else {
        std::cerr << "Ошибка при выполнении запроса: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}


void showMainMenu() {
    std::cout << "1. Создать таблицу (Меню)\n";
    std::cout << "2. Добавить данные (Меню)\n";
    std::cout << "3. Выбрать данные (Меню)\n";
    std::cout << "4. Обновить данные (Меню)\n";
    std::cout << "5. Удалить данные (Меню)\n";
    std::cout << "6. Ручной ввод SQL\n";
    std::cout << "7. Выход\n";
    std::cout << "Выберите опцию: ";
}

int main() {

    setlocale(LC_ALL, "ru");

    sqlite3* db;
    int rc = sqlite3_open("database.db", &db); 
    if (rc) {
        std::cerr << "Ошибка при открытии базы данных: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    int choice;
    do {
        showMainMenu();
        std::cin >> choice;
        std::cin.ignore(); 

        switch (choice) {
        case 1: {
            std::string* tableName = new std::string;
            std::string* sql = new std::string;
            std::cout << "Введите название таблицы: ";
            std::getline(std::cin, *tableName);
            std::cout << "Введите SQL-запрос для создания таблицы (например, CREATE TABLE " << *tableName << " (id INTEGER PRIMARY KEY, name TEXT));\n";
            std::getline(std::cin, *sql);
            executeSQL(db, *sql);
            delete tableName;
            delete sql;
            break;
        }
        case 2: {
            std::string* tableName = new std::string;
            std::string* sql = new std::string;
            std::cout << "Введите название таблицы: ";
            std::getline(std::cin, *tableName);
            std::cout << "Введите SQL-запрос для вставки данных (например, INSERT INTO " << *tableName << " (name) VALUES ('Alice'));\n";
            std::getline(std::cin, *sql);
            executeSQL(db, *sql);
            delete tableName;
            delete sql;
            break;
        }
        case 3: {
            std::string* tableName = new std::string;
            std::string* sql = new std::string;
            std::cout << "Введите название таблицы: ";
            std::getline(std::cin, *tableName);
            std::cout << "Введите SQL-запрос для выборки данных (например, SELECT * FROM " << *tableName << ");\n";
            std::getline(std::cin, *sql);
            executeQuery(db, *sql);
            delete tableName;
            delete sql;
            break;
        }
        case 4: {
            std::string* tableName = new std::string;
            std::string* sql = new std::string;
            std::cout << "Введите название таблицы: ";
            std::getline(std::cin, *tableName);
            std::cout << "Введите SQL-запрос для обновления данных (например, UPDATE " << *tableName << " SET name = 'Bob' WHERE id = 1);\n";
            std::getline(std::cin, *sql);
            executeSQL(db, *sql);
            delete tableName;
            delete sql;
            break;
        }
        case 5: {
            std::string* tableName = new std::string;
            std::string* sql = new std::string;
            std::cout << "Введите название таблицы: ";
            std::getline(std::cin, *tableName);
            std::cout << "Введите SQL-запрос для удаления данных (например, DELETE FROM " << *tableName << " WHERE id = 1);\n";
            std::getline(std::cin, *sql);
            executeSQL(db, *sql);
            delete tableName;
            delete sql;
            break;
        }
        case 6: {
            std::string* sql = new std::string;
            std::cout << "Введите SQL-запрос (или 'exit' для выхода):\n";
            while (true) {
                std::cout << "> ";
                std::getline(std::cin, *sql);
                if (*sql == "exit") break;
                executeQuery(db, *sql);
            }
            delete sql;
            break;
        }
        case 7: std::cout << "Выход...\n"; break;
        default: std::cout << "Неверный выбор. Попробуйте снова.\n"; break;
        }
    } while (choice != 7);

    sqlite3_close(db);
    return 0;
}