- Implemented a Main function which takes in input and then tokenises it
- SystemP() is called from main 
- based on command, SystemP() calls relevant functions stored in files
- functions like pwd, echo , cd, ls are implemented in pwd.c, echo.c, cd.c, ls.c respectively
- foreground and background functions are handled by process.c
- signal(SIGCHLD, processTerminated); runs in main.c to check for termination of background processes and then calls processTerminated in process.c
- history is stored in history.txt
    - on starting shell, the history stored in history.txt is read into the history array
    - throughout execution of the shell, various commands are stored in the circular array history
    - on exit(), the array is written to the history.txt
- repeat command causes a for loop on the command given

prompt.c    ->      prints the prompt taking into account current directory
main.c      ->      takes input and calls systemP()
system.c    ->      handles commands
process.c   ->      handles and executes foreground and background processes
utils.h     ->      contains commonly used variables
cd.c        ->      implements cd functionality
ls.c        ->      implements ls functionality
echo.c      ->      implements echo functionality
pinfo.c     ->      implements pinfo functionality
history.c   ->      implements history functionality
pwd.c       ->      implements pwd functionality
makefile    ->      contains gcc command, helps in compiling

