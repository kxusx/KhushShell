#include "cd.h"
#include "system.h"
#include "headers.h"
#include "utils.h"
#include "prompt.h"
#include "echo.h"
#include "process.h"
 
int main()
{   
    char pe[2000];
    char s[10] = " \r\t\n";
    getcwd(pe, sizeof(pe));
    strcpy(HomeDir,pe);
    strcpy(prevdir, HomeDir);
    
    signal(SIGCHLD,processTerminated);

    while (1)
    {   
        
        i = 0;
        prompt();
        
        fgets(input, 1000, stdin);
        
        token = strtok(input, s);
        while (token != NULL){
            strcpy(args[i], token);
            token = strtok(NULL, s);
            i++;
        }
       
        if (strcmp(input, "exit") == 0)
            break;
       
        systemP();
       
    }
    return 0;
}
