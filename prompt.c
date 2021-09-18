#include "system.h"
#include "headers.h"
#include "utils.h"
#include "prompt.h"
#include "echo.h"

void prompt()
{ 
    char CurrDir[500];
    char *curr=malloc(500);
    char s[10] = ".";
    //printf("\nin prompt\n");
    gethostname(hostname, 500);
    getlogin_r(name, 32);
    token = strtok(hostname, s);

    getcwd(CurrDir, sizeof(CurrDir));
    strcpy(curr,CurrDir);
    //printf("\ncurr in prompt : %s\nsize of curr:%lu\nsize of homedir:%lu\n",curr,strlen(curr),strlen(HomeDir));


    if (strcmp(CurrDir, HomeDir) == 0)
    {
        printf("%s@%s:~>", name, token);
    }
    else if (strstr(CurrDir, HomeDir))
    {  
        printf("%s@%s:%s>", name, token, CurrDir + strlen(HomeDir) + 1);
         
    }else{
        printf("%s@%s:%s>", name, token, CurrDir);
    }

    
 //printf("\n4prompt\n");
    
}
//
    // char *ssc;

    //
    // printf("%s@%s:~>", name, token);

    //  ssc = strtok(CurrDir,p);
    //  printf("\n%s",HomeDir);
    //  printf("\n%s",CurrDir);

    //  printf("\n%s",ssc);

    // if(strstr(CurrDir,HomeDir)==0){

    // }
    //printf("token : %s\n",token);