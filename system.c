#include "cd.h"
#include "system.h"
#include "headers.h"
#include "utils.h"
#include "echo.h"
#include "ls.h"
#include "pinfo.h"
#include "pwd.h"
#include "process.h"
#include "history.h"
#include "redirection.h"

void systemP()
{
    if (redflag == 1 || redflag == 2)
    {   
        redirectionQ();
       
    }
    else if (strcmp(QCommands[0], "echo") == 0)
    {
    
        echoP(QCommands);
    }
    else if (strcmp(QCommands[0], "cd") == 0)
    {
        if (cdQ())
        {
            perror("Error from cd");
        }
    }
    else if (strcmp(QCommands[0], "pinfo") == 0)
    {
        pinfoP();
    }
    else if (strcmp(QCommands[0], "pwd") == 0)
    {
        pwdP();
    }
    else if (strcmp(QCommands[0], "ls") == 0)
    {
        lsP(QCommands);
    }
    else if (strcmp(QCommands[0], "history") == 0)
    {
        historyP();
        printH();
    }
    else if (strcmp(QCommands[0], "repeat") == 0)
    {
        int counter = atoi(QCommands[1]);
        for (int k = 2; k < i; k++)
        {
            strcpy(QCommands[k - 2], QCommands[k]);
        }
        i = i - 2;
        for (int j = 0; j < counter; j++)
        {
            systemP();
        }
    }
    else
    {
        if (QCommands[i - 1][0] != '&')
        {
            foreground(QCommands);
        }
        else
        {
            i--;
            background(QCommands);
        }
    }
}