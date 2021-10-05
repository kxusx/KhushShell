#include "pinfo.h"
#include "headers.h"
#include "utils.h"

void pinfoP(char args[1000][1000])
{
    pid_t pid;
    int f;
    char buf[1000], fileName[1000], pinfo[1000][1000], pidstat[1000], pidexe[1000], *tok, pu[1000];
    int c; // args[1]
    if (i == 1)
    {
        pid = getpid();
    }
    else
    {
        c = atoi(args[1]);
        pid = c;
    }

    sprintf(pidstat, "/proc/%d/stat", pid);
    f = open(pidstat, O_RDONLY);
    //f = open("ptr.txt", O_RDONLY);

    if (f < 0)
    {
        perror("Process doesnt exist");
        return;
    }
    else
    {
        FILE *fp;
        int r = read(f, buf, 10000);

        int k = 0;
        tok = strtok(buf, " ");
        while (tok != NULL)
        {
            strcpy(pinfo[k], tok);
            //printf("pinfo[%d]:%s\n", k, pinfo[k]);
            tok = strtok(NULL, " ");
            k++;
        }

        printf("pid -- %d\n", pid);
        printf("Process Status -- {%s", pinfo[2]);
        if (strcmp(pinfo[0], pinfo[7]) == 0)
        {
            printf("+}\n");
        }
        else
        {
            printf("}\n");
        }
        printf("Memory -- %s {Virtual Memory}\n", pinfo[22]);
    }

    sprintf(pidexe, "/proc/%d/exe", pid);
    int x = readlink(pidexe, buf, sizeof(buf));
    printf("Executable path -- ");
    if (x <= 0)
    {
        perror("Readlink error");
        return;
    }
    else
    {
        buf[x] = 0;
        strcpy(pu, buf);
        char *r;
        r = strstr(pu, HomeDir);
        if (r)
        {
            char output[500] = "";
            strncpy(output, pu + strlen(HomeDir), strlen(pu) - strlen(HomeDir));
            printf("~%s\n", output);
        }
        else
        {
            printf("%s\n", pu);
        }
    }
    printf("\n");
    close(f);
}