#include "cd.h"
#include "system.h"
#include "headers.h"
#include "utils.h"
#include "prompt.h"
#include "echo.h"
#include "process.h"
#include "history.h"
#include "redirection.h"

int main()
{
    char pe[2000];
    char s[10] = " \r\t\n";
    char fp[100] = ";";
    char *tokencol;
    getcwd(pe, sizeof(pe));
    strcpy(HomeDir, pe);
    strcpy(prevdir, HomeDir);
    int noOfCommands = 0, pos = 0;
    char comms[1000][1000];

    signal(SIGCHLD, processTerminated);
    initialize();

    while (1)
    {
        noOfCommands = 0;
        i = 0, k = 0, redflag = 0;
        prompt();

        fgets(input, 1000, stdin);

        if (strcmp(input, "exit") == 0)
        {
            history_checker();
            break;
        }

        //tokenising based on ';'
        token = strtok(input, ";\n");
        while (token != NULL)
        {
            strcpy(tempargs[k], token);
            token = strtok(NULL, ";\n");
            k++;
        }

        //tokenising based on " "
        for (int j = 0; j < k; j++)
        {
            strcpy(binput, tempargs[j]);
            //printf("binput:%s\n",binput);
            i = 0;
            token = strtok(tempargs[j], s);

            while (token != NULL)
            {
                strcpy(args[i], token);
                strcpy(QCommands[i], token);
                token = strtok(NULL, s);
                i++;
            }

            if (strcmp(args[0], "history") != 0)
            {
                history_checker();
            }

            for (int j = 0; j < i; j++)
            {
                for (int l = 0; args[j][l]; l++)
                {
                    if ((args[j][l] == '>') || args[j][l] == '<' || (args[j][l] == '>' && args[j][l + 1] == '>') && redflag == 0)
                    {
                        if (args[j][l] == '>' && args[j][l + 1] == '>')
                            l++;
                        redflag = 1;
                    }
                    else if ((args[j][l] == '>') || args[j][l] == '<' || (args[j][l] == '>' && args[j][l + 1] == '>') && redflag == 1)
                    {
                        if (args[j][l] == '>' && args[j][l + 1] == '>')
                            l++;
                        redflag = 2;
                    }
                }
            }

            systemP();

            
        }
    }
    writeToHistory();
    return 0;
}
