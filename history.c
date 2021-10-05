#include "history.h"
#include "headers.h"
#include "utils.h"

void printArray()
{
    for (int o = 0; o < 20; o++)
    {
        printf("his[%d]:%s\n", o, history[o]);
    }
}

int hsize = 0, n = 19;
void initialize()
{
    size_t nameSize;
    char *name = malloc(1000);
    ssize_t read;
    char currentDir[1000];
    getcwd(currentDir, sizeof(currentDir));
    char filename[1000];
    strcpy(filename, currentDir);
    strcat(filename, "/history.txt");
    front = -1;
    end = -1;

    FILE *fp = fopen(filename, "r");
    fflush(stdin);
    if (!fp)
    {
       // printf("Error opening file for Reading '%s'\n", filename);
    }
    if (fp)
    {

        while (end < 20 && (read = getline(&name, &nameSize, fp) != -1))
        {
            end++;
            if (name[strlen(name) - 1] == '\n')
            {
                name[strlen(name) - 1] = '\0';
            }
            strcpy(history[end], name);
        }
    }
    if (end >= 0)
    {
        front = 0;
    }
    // printArray();
    // printf("final end:%d\n", end);
    fclose(fp);
    free(name);
}

void writeToHistory()
{
    char currentDir[1000];
    getcwd(currentDir, sizeof(currentDir));
    char filename[1000];
    strcpy(filename, currentDir);
    strcat(filename, "/history.txt");
    FILE *fp = fopen(filename, "w");
    if (!fp)
    {
        fprintf(stderr, "Write Error opening file '%s'\n", filename);
    }
    if (fp)
    {
        int k;
        for (k = front; k != end; k = (k + 1) % 20)
        {
            //printf("history[%d]:%s\n", k, history[k]);
            fprintf(fp, "%s\n", history[k % 20]);
        }
        fprintf(fp, "%s\n", history[k]);
       // printf("history[%d]:%s\n", k, history[k]);
    }
    fclose(fp);
}

void history_checker()
{
    if (binput[strlen(binput) - 1] == '\n')
    {
        binput[strlen(binput) - 1] = '\0';
    }
    int flag = 0, k;
    k = (end + 20)%20;
    //printf("\nend:%dcheck k : %d\n",end, k);
    if (strcmp(binput, history[k]) == 0)
    {
        flag = 1;  
    }

    if (flag == 0)
    {
        historyP();
    }
    else
    {
        ;
    }
}

void historyP()
{
    //printf("\nHistory Binput:%s\n",binput);
    if (binput[strlen(binput) - 1] == '\n')
    {
        binput[strlen(binput) - 1] = '\0';
    }
    
    if ((front == 0 && end == 19) || (end == (front - 1) % (n - 1)))
    {
        front = (front + 1) % 20;
        end = (end + 1) % 20;
        strcpy(history[end], binput);
    }
    else if (front == -1)
    {
        front = 0;
        end = 0;
        strcpy(history[end], binput);
    }
    else if (end == n - 1 && front != 0)
    {
        end = 0;
        strcpy(history[end], binput);
    }
    else
    {
        end++;
        strcpy(history[end], binput);
    }
    //printArray();
}

void printH()
{
    int c, ending, starting,k;
    
    

    if (i == 2)
    {
        c = atoi(args[1]);
        for (k = (end + 20 + 1- c)%20; k %20 != (end+20)%20; k++)
        {  
            k = ( k + 20)%20;
            printf("%s\n", history[k]);
        }
        printf("%s\n", history[k]);
        
    }
    else
    {   
        for (k = front; k %20 != end%20; k++)
        {    
            k = ( k + 20)%20;
            printf("%s\n",history[k]);
        }
        printf("%s\n", history[k]);
    }
}