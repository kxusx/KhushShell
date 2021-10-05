#include "process.h"
#include "headers.h"
#include "utils.h"
#include "redirection.h"
#include "system.h"


int appendFlag = 0,inpQ=0,outQ=0, a = 0, fds[10], c = 0;
char *command[1000], to[10000], *from[10000], *temp1[1000], temp2[1000], input_file[100000], delim[10], output_file[100000];

void b(){
    c=0;
    strcpy(output_file, "");
    strcpy(input_file, "");
    for (int j = 0; j < 10; j++)
        fds[j] = -1;
    if (appendFlag == 1)
        strcpy(delim, ">>");
    else
        strcpy(delim, ">");

    // tokening based on '>' or '>>'
    token = strtok(binput, delim);
    while (token != NULL)
    {
        //printf("token1:%s\n", token);
        command[c] = token;
        token = strtok(NULL, delim);
        c++;
    }
   
    // tokening to get the output file name
    if (c == 2)
    {
        strcpy(to, command[1]);
        token = strtok(to, " \t\n\r");
        strcpy(output_file, token);
    }
    //printf("Output file:%s\n", output_file);

    // tokening based on '<'
    c = 0;
    token = strtok(command[0], "<");
    while (token != NULL)
    {
        //printf("token2:%s\n", token);
        temp1[c] = token;
        token = strtok(NULL, "<");
        c++;
    }

    // tokening to get the input file name
    if (c == 2)
    {
        strcpy(to, temp1[1]);
        token = strtok(to, " \t\n\r");
        strcpy(input_file, token);
    }
   // printf("Input file:%s\n", input_file);

    i = 0;
    token = strtok(temp1[0], " \t\n\r");
    while (token != NULL)
    {
        strcpy(QCommands[i], token);
        token = strtok(NULL, " \t\n\r");
        i++;
    }

    //  printf("QComms : ");
    // for (int j = 0; j < i; j++)
    // {
    //     printf("%s ", QCommands[j]);
    // }
    // printf("\n");

    if (strcmp(input_file, "") != 0 && strcmp(output_file, "") == 0) // input redirection
    {
        //printf("INPUT\n");
        redflag = 0;
        originalIN = dup(STDIN_FILENO);

        fds[0] = open(input_file, O_RDONLY);
        if (fds[0] < 0)
            perror("File doesn't exist\n");

        dup2(fds[0], STDIN_FILENO);
        systemP();
        dup2(originalIN, STDIN_FILENO);
    }
    else if (strcmp(output_file, "") != 0 && strcmp(input_file, "") == 0) //output redirection
    {
        //printf("OUTPUT\n");
        redflag = 0;
        dup2(STDOUT_FILENO, originalOUT);
        if (appendFlag == 0){
            fds[0] = open(output_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
            if (fds[0] < 0)
            perror("File doesn't exist YOLO");}
        else if (appendFlag == 1)
            fds[0] = open(output_file, O_APPEND | O_WRONLY | O_CREAT, 0644);

        if (dup2(fds[0], STDOUT_FILENO) < 0)
        {
            printf("Unable to duplicate file descriptor");
        }
        systemP();
        dup2(originalOUT, STDOUT_FILENO);
        close(fds[0]);
    }
    else                                                                // both input and output
    {   
        int originalOUT,originalIN;
        redflag = 0;
        originalIN = dup(STDIN_FILENO);
        originalOUT = dup(STDOUT_FILENO);

        fds[0] = open(input_file, O_RDONLY); //for input file
        if (fds[0] < 0)
            perror("File doesn't exist\n");

        if (appendFlag == 0) // for output file
            fds[1] = open(output_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
        else if (appendFlag == 1)
            fds[1] = open(output_file, O_APPEND | O_WRONLY | O_CREAT, 0644);

        dup2(fds[1], STDOUT_FILENO);
        dup2(fds[0], STDIN_FILENO);
        systemP();
        dup2(originalIN, STDIN_FILENO);
        dup2(originalOUT, STDOUT_FILENO);
        close(fds[0]);
        close(fds[1]);
    }
}

void redirectionQ()
{
    for (int j = 0; j < i; j++)
    {
        if (strcmp(args[i], ">") == 0)
            outQ += 1;
        else if (strcmp(args[i], "<") == 0)
            inpQ += 1;
        else if (strcmp(args[i], ">>") == 0)
        {
            appendFlag = 1;
            a += 1;
        }
    }
    b();
}