#include "pinfo.h"
#include "headers.h"
#include "utils.h"

void pinfoP()
{
    // int id;
    // pid_t cpid;
    // char path[1000];
    // char buffer[1000];
    // if (i == 1)
    // {
    //     cpid = getpid();
    // }
    // else
    // {
    //     cpid = atoi(args[1]);
    // }
    // printf("pid -- %d\n", cpid);
    // sprintf(path, "/proc/%d/stat", cpid);
    // printf("path: %s\n", path);

    // FILE *fp = fopen(path, "r");
    // printf("%s\n", fp);
    // if (!fp)
    // {
    //     perror("Error while opening the proc/pid/status file\n");
    // }
    // else
    // {
    //     char state;
    //     fgets(buffer, 256, fp);
    //     fgets(buffer, 256, fp);
    //     sscanf(buffer, "State:\t%c", &state);
    //     printf("Process Status -- %c\n", state);
    //     fclose(fp);
    // }
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
