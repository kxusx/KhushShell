#include "process.h"
#include "headers.h"
#include "utils.h"
#include "prompt.h"

typedef struct processes processBG;
int processCount = 0;
struct processes
{
    pid_t pid;
    int isRunning;
    char name[500];
    struct processes *next;
};

processBG *head = NULL;
processBG *current = NULL;

void insert(pid_t pid, int isRunning, char name[500])
{
    processBG *new = (processBG *)malloc(sizeof(processBG));
    new->pid = pid;
    new->isRunning = isRunning;
    strcpy(new->name, name);
    new->next = head;
    head = new;
}

char *delete (pid_t pid)
{   
    processBG *prev;
    processBG *current = head;
    prev = current;
    if (head == NULL)
    { 
        return NULL;
    }
    while (current->pid != pid)
    {
        if (current->next == NULL)
        {
            return NULL;
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }
    prev->next = current->next;
    return current->name;
}

// pid_t *find(pid_t pid)
// {
//     processBG *current = head;
//     if (head == NULL)
//     {
//         return 0;
//     }
//     while (current->pid != pid)
//     {
//         if (current->next == NULL)
//         {
//             return 0;
//         }
//         else
//         {
//             current = current->next;
//         }
//     }
//     return current->pid;
// }

int foreground()
{   
    
    pid_t pid = fork();
    
    char *arguments[1000];
    for (int j = 0; j < i; j++)
    {
        arguments[j] = malloc(500);
        strcpy(arguments[j], args[j]);
    }
    arguments[i] = NULL;

    if (pid < 0)
    {
        printf("Forking error\n");
        return 0;
    }
    else if (pid == 0) //child
    {
        if (execvp(arguments[0], arguments) < 0)
        {
            printf("Command '%s' not found\n", args[0]);
        }
        exit(0);
    }
    else
    {
        wait(0);
    }
    return 0;
}

int background()
{
    pid_t pid = fork();

    char *arguments[1000];
    for (int j = 0; j < i; j++)
    {
        arguments[j] = malloc(500);
        strcpy(arguments[j], args[j]);
    }
    arguments[i] = NULL;

    if (pid < 0)
    {
        printf("Forking error\n");
        return 0;
    }
    else if (pid == 0) //child
    {
        if (execvp(arguments[0], arguments) < 0)
        {
            printf("Command '%s' not found\n", args[0]);
        }
        exit(0);
    }
    else
    {
        insert(pid, 1, arguments[0]);
        processCount++;
    }
    return 0;
}

void processTerminated()
{
    int flag, c;
    pid_t temp;
    int final_pid;
    char *processName = malloc(5000);
    temp = waitpid(-1, &flag, WNOHANG | WUNTRACED);
    // c = find(temp);

    if (temp > 0)
    {
        processName = delete (temp);
       // printf("\npr:%s",processName);
        if (!processName)
        {
            printf("\n");
        }
        else
        {
            if (WIFEXITED(flag))
            {
                fprintf(stderr, "\n%s with pid %d exited normally\n", processName, temp);
            }
            else
            {
                fprintf(stderr, "\n%s with pid %d exited NOT normally\n", processName, temp);
            }
            prompt();
        }
    }
    fflush(stderr);
    fflush(stdout);
    
    
}