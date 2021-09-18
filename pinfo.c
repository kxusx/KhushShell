#include "pinfo.h"
#include "headers.h"
#include "utils.h"

void pinfoP()
{
    int id;
    id = getpid();
    char pidstat[500];
    strcpy(pidstat, "/linprocfs/");
    char idchar[500];
    sprintf(idchar, "%d", id);
    strcat(pidstat, idchar);

    char execstat[500];
    strcpy(execstat, pidstat);

    strcat(pidstat, "/stat");
    strcat(execstat, "/exe");

    int printerr = 0;

    int fd = open(pidstat, O_RDONLY);
    if (fd < 0)
    {
        
        printf("Process doesnt exist\n");
        printerr = 1;
    }
    else
    {
        char statbuff[10000];
        read(fd, statbuff, 10000);
        char *pinfoarg = strtok(statbuff, " ");

        printf("pid -- %s\n", pinfoarg);

        pinfoarg = strtok(NULL, " ");
        pinfoarg = strtok(NULL, " ");

        printf("Process Status -- %s\n", pinfoarg);

        for (int i = 0; i < 20; i++)
            pinfoarg = strtok(NULL, " ");

        printf("Memory -- %s\n", pinfoarg);
    }

    char execbuff[10000];
    int t = readlink(execstat, execbuff, 10000);
    if (t < 0)
    {
        if (printerr == 0)
        {
            
            printf("Readlink error\n");
        
        }
    }
    else
        printf("Executable path -- %s\n", execbuff);

    close(fd);
}

// History
// array 21 size 
//     - only allow 20 size
//     - when inserting after 20, put in at 21, start at 1, write it to file
//     - make start at 0, when reading 

// - first read
// - add on array
// - put into file
// read

// Functions : 
// to READ
// to ADD ( which will read and write)
// to WRITE
// to print    (which will need read)
