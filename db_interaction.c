//
// Created by pmsli on 15/01/2019.
//
#include <stdio.h>
#include "sqlite3.h"

/*
int create_db (void){
    sqlite3 *logDB;
    sqlite3_stmt *res;

    char  *err_msg = 0;

    int rc = sqlite3_open(":memory:", &logDB);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(logDB));
        sqlite3_close(logDB);

        return 1;
    }

    rc = sqlite3_prepare_v2(logDB, "SELECT SQLITE_VERSION()", -1, &res, 0);

    if(rc != SQLITE_OK){
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(logDB));
        sqlite3_close(logDB);

        return 1;
    }

    rc = sqlite3_step(res);

    if(rc == SQLITE_ROW){
        printf("%s\n",sqlite3_column_text(res,0));
    }
}
*/
