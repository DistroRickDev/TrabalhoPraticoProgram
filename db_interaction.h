//
// Created by Utilizador on 17/01/2019.
//

#ifndef LOGIN_W_STRUCT_DB_INTERACTION_H
#define LOGIN_W_STRUCT_DB_INTERACTION_H
void  checkForDB(void);
void insertWorker(char *name, char *rfid, char *password, float salary);
void insertLog(char *rfid, int type);
void deleteWorker (char *name);
void listWorkers (char *name);
void listLogs (char *rfid, int type);
void medTempo (char *rfid);
#endif //LOGIN_W_STRUCT_DB_INTERACTION_H
