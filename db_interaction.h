//
// Created by Utilizador on 17/01/2019.
//

#ifndef LOGIN_W_STRUCT_DB_INTERACTION_H
#define LOGIN_W_STRUCT_DB_INTERACTION_H
void  checkForDB(void);
void insertWorker(char *name, char *rfid, char *password, float salary);
void insertLog(char *rfid, int time, int type);
#endif //LOGIN_W_STRUCT_DB_INTERACTION_H
