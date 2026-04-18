#include "Database.h"

Database::Database(const char *path) {
    if (sqlite3_open(path, &db)) {
        std::cout << "Failed to open database\n" << std::endl;
    }
    else {
        std::cout << "Database opened successfully\n" << std::endl;
    }
}

Database::~Database() {
    sqlite3_close(db);
}

sqlite3* Database::Get() {
    return db;
}


