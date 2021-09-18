#include "pwd.h"
#include "headers.h"
#include "utils.h"

void pwdP(){
    char currentDirectory[1000];
     getcwd(currentDirectory, sizeof(currentDirectory));
    printf("%s\n",currentDirectory);
}