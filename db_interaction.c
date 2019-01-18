//
// Created by pmsli on 15/01/2019.
//
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "sqlite3.h"

static int callback(void *data, int argc, char **argv, char **azColName) {
    int i;
    fprintf(stderr, "%s: ", (const char *) data);

    for (i = 0; i < argc; i++) {
        printf("%s ----> %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}
static int callbackmed(void *data, int argc, char **argv, char **azColName) {
    int i;
    int indic = 0;
    long int somaM = 0;
    long int somam = 0;
    fprintf(stderr, "%s: ", (const char *) data);

    for (i = 0; i < argc; i++) {
        printf("%s ----> %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        if(azColName[i]=="TYPE" && argv[i] == "1")
        {
            indic = 1;
        }
        else
            indic = 0;
        if(azColName[i]=="TIME")
        {
            if(indic == 0){
                somaM += argv[i];
            }
            else
                somam += argv[i];
        }
    }
    printf("%ld",somaM - somam);

    printf("\n");
    return 0;
}

void dbCreation() {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;



    rc = sqlite3_open("checkpointDATA.db", &db);

    if (rc) {
        fprintf(stderr, "Can't Create database due to: %s\n", sqlite3_errmsg(db));
    } else {
        fprintf(stderr, "Created database successfully\n");
    }

    /* Create SQL table Workers */
    sql = "CREATE TABLE WORKERS("  \
      "ID INTEGER PRIMARY KEY     AUTOINCREMENT," \
      "NAME           TEXT    NOT NULL," \
      "RFID           TEXT    NOT NULL," \
      "PASSWORD       TEXT    NOT NULL," \
      "SALARY         REAL    NOT NULL);";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error creating Workers: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Table workers created successfully\n");
    }

    /* Create SQL table LOGS */
    sql = "CREATE TABLE LOGS("  \
      "ID INTEGER PRIMARY KEY," \
      "RFID           TEXT    NOT NULL," \
      "TIME           INT     NOT NULL," \
      "TYPE           INT     NOT NULL);";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error creating LOGS: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Table LOGS created successfully\n");
    }


    sqlite3_close(db);
}

void checkForDB() {

    if( access( "checkpointDATA.db" , F_OK ) != -1 ) {
        fprintf(stderr, "Loaded database successfully\n");
    } else {
        fprintf(stderr,"Can't find database creating from scratch\n");
        dbCreation();
    }
}

void insertLog(char *rfid, int type) {

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char sql[5000];
    char times[11];
    snprintf(times, sizeof(times), "%lu", (unsigned long)time(NULL));

    rc = sqlite3_open("checkpointDATA.db", &db);

    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }

    snprintf( sql, sizeof(sql), "INSERT INTO LOGS VALUES (NULL, '%s', '%d', '%d' );", rfid, times, type);

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Records created successfully\n");
    }
    sqlite3_close(db);
}

void insertWorker(char *name, char *rfid, char *password, float salary) {

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char sql[5000];

    rc = sqlite3_open("checkpointDATA.db", &db);

    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }

    snprintf( sql, sizeof(sql), "INSERT INTO WORKERS VALUES (NULL, '%s', '%s', '%s', '%f' );",name, rfid, password, salary);

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Records created successfully\n");
    }
    sqlite3_close(db);
}

void deleteWorker (char *name){
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char sql[5000];

    rc = sqlite3_open("checkpointDATA.db", &db);

    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }

    snprintf( sql, sizeof(sql), "DELETE FROM WORKERS WHERE NAME='%s';",name);

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Records deleted successfully\n");
    }
    sqlite3_close(db);
}

void listWorkers (char *name){

    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("checkpointDATA.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n",
                sqlite3_errmsg(db));
        sqlite3_close(db);

    }

    char sql[300];
    snprintf( sql, sizeof(sql), "SELECT ID,NAME FROM WORKERS WHERE NAME GLOB '*%s*';",name);


    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

    }

    sqlite3_close(db);
}

void listLogs (char *rfid, int type){

    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("checkpointDATA.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n",
                sqlite3_errmsg(db));
        sqlite3_close(db);

    }

    char sql[300];
    snprintf( sql, sizeof(sql), "SELECT ID,RFID,TIME,TYPE FROM LOGS WHERE RFID = '%s' AND TYPE = %d;",rfid,type);


    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

    }

    sqlite3_close(db);

}

void listAllLogs (int type){

    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("checkpointDATA.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n",
                sqlite3_errmsg(db));
        sqlite3_close(db);

    }

    char sql[300];
    snprintf( sql, sizeof(sql), "SELECT ID,RFID,TIME,TYPE FROM LOGS WHERE TYPE = %d;",type);


    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

    }

    sqlite3_close(db);

}

void medTempo (char *rfid){

    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("checkpointDATA.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n",
                sqlite3_errmsg(db));
        sqlite3_close(db);

    }

    char sql[300];
    snprintf( sql, sizeof(sql), "SELECT TYPE,TIME FROM LOGS WHERE RFID = '%s'",rfid);


    rc = sqlite3_exec(db, sql, callbackmed, 0, &err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

    }

    sqlite3_close(db);

}
