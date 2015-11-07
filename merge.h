//
// Created by anchit on 31/10/15.
//

#ifndef MERGE_MERGE_H
#define MERGE_MERGE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

void err(char *message)
{
    perror(message);
    exit(-1);
}

#endif //MERGE_MERGE_H
