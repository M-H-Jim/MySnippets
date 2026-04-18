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

void Database::PrintFolders() {
    const char *sql = "SELECT id, name FROM folders;";
    sqlite3_stmt *stmt;
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const char *name = (const char *)sqlite3_column_text(stmt, 1);
            
            std::cout << id << " - " << name << std::endl;
        }
    }
    
    sqlite3_finalize(stmt);
}
