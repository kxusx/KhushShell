#ifndef __PROCESS_H
#define __PROCESS_H

int foreground(char args[1000][1000]);
int background(char args[1000][1000]);
void processTerminated();
#endif