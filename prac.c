#include "cd.h"
#include "headers.h"
#include "utils.h"
 
int main()
{
    char temp[1000];
    char HomeDir[1000];
    char currDir[1000];
    getcwd(HomeDir, sizeof(HomeDir));
    printf("Homedir:%s\n",HomeDir);
    char *t = malloc(1000);
    strcpy(t,"hi");
    chdir(t);
    printf("thhj:%s\n",t);
    getcwd(currDir, sizeof(currDir));
    printf("Currdir:%s\n",currDir);
    return 0;
}

