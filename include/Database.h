#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <vector>
#include <sqlite3.h>

class Database {
    private:
        sqlite3 *db;
    
    public:
        Database(const char *path);
        ~Database();
        
        sqlite3* Get();
        void PrintFolders();
};


#endif // DATABASE_H
