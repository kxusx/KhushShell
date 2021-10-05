#include "cd.h"
#include "headers.h"
#include "utils.h"
 
int cdQ()
{
    char temp[1000];
    char *t = malloc(1000);
    getcwd(temp, sizeof(temp));
    if(i==1){
        chdir(HomeDir);
    }
    else if(strcmp(args[1], "~") == 0 || strcmp(args[1], " ") == 0)
    {
        chdir(HomeDir);
    }
    else if(strcmp(args[1], "-") == 0)
    {
        chdir(prevdir);
    }
    else if(chdir(args[1]))
    {
        return -1;
    }
    strcpy(prevdir, temp);
   //printf("prevdir:%s\n",prevdir);
    return 0;
}



