//
// Created by Stive on 04/06/2023.
//

#ifndef PROJET_COMMANDES_H
#define PROJET_COMMANDES_H
struct command {
    char name[50];
    int int_size;
    int int_params[10];
    int str_size;
    char * str_params[10];
};
typedef struct command Command;

Command* create_command();
void add_str_param(Command* cmd, char * p);
void add_int_param(Command*cmd,int p);
void free_cmd(Command *cmd);
int read_exec_command(Command* cmd,Area * area);
void read_from_stdin(Command* cmd);
#endif //PROJET_COMMANDES_H
