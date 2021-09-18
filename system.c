#include "cd.h"
#include "system.h"
#include "headers.h"
#include "utils.h"
#include "echo.h"
#include "ls.h"
#include "pinfo.h"
#include "pwd.h"
#include "process.h"

void systemP()
{  
    if (strcmp(args[0], "echo") == 0)
    {
       echoP();
    }
    else if (strcmp(args[0], "cd") == 0)
    {   
         if(cdQ()){
            perror("Error from cd");
        }
    }
    else if (strcmp(args[0], "pinfo") == 0)
    {   
         pinfoP();
    }
    else if (strcmp(args[0], "pwd") == 0)
    {   
        pwdP();
    }else if(strcmp(args[0],"ls")==0){
        lsP();
    }
    else{
        if (args[i-1][0] != '&')
        {   
            
            foreground();
        }
        else
        {   
            i--;
            
            // for(int j=0;j<i;j++){
            //     printf("args[%d]:%s\n",j,args[j]);
            // }
            //printf("background\n");
            background();
        }
    }
}