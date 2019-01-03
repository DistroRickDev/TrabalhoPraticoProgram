
#ifndef LOGIN_W_STRUCT_ADMIN_SETUP_H
#define LOGIN_W_STRUCT_ADMIN_SETUP_H

char tokenGenerator(char token[]);
void userSetup(int *reg);
void checkAdmin(int *reg);
void listAdm();
void admWrite();
void readAdm();
int writeReg(int *reg);
int readReg(int *reg);
char *writeToken(char token[]);
char *readToken(char token[]);

#endif //LOGIN_W_STRUCT_ADMIN_SETUP_H
