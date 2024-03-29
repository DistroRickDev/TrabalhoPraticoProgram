
#ifndef LOGIN_W_STRUCT_ADMIN_SETUP_H
#define LOGIN_W_STRUCT_ADMIN_SETUP_H

void adminSetup(int *reg);
void checkAdmin(int *reg);
void listAdm();
void writeAdm();
void readAdm();
int writeReg(int *reg);
int readReg(int *reg);
void admReset(int *reg);
void writeToken(char id[]);
int readToken();
char *readRFID(char id[]);

#endif //LOGIN_W_STRUCT_ADMIN_SETUP_H
