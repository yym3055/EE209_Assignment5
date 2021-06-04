#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 2000
#define MAX_ARG_NUM 2000

int i, pid;
char *token, command[MAX_INPUT_LENGTH], 
*arguments[MAX_ARG_NUM];

int main() {
    while(1){
        if (fgets(command, sizeof(command), stdin) == NULL) {
            fprintf(stderr ,"empty errorneous input occured.\n");
            continue;
            } 
        // set the last '\n' character to '\0'.
        command[strlen(command)-1] = 0; 
        
        token = strtok(command, " ");
        if (token == NULL) continue; // null command. just skip
        
        if (strcmp(token, "exit") == 0) {exit(0);} // handle exit command

        arguments[0] = token;
        for (i = 1; i < MAX_ARG_NUM; i++) {
            token = strtok(NULL, " ");
            if (token == NULL) break;
            arguments[i] = token;
        }
        arguments[i] = NULL;

        pid = fork();
        if (pid != 0) {
            wait(NULL); // parent process
        } else { // child process
            if (execvp(arguments[0], arguments) == -1) {
                fprintf(stderr, "cannot execute the command: %s\n", arguments[0]);
                continue;
            }
        }
    }
    return 0;
}
