//
//  Error.cpp
//  Vanilla
//
//  Created by ZengHongru on 16/4/13.
//
//

#include "Error.h"

#include <string.h>
#include <unistd.h>
#include <sys/errno.h>
#include <stdlib.h>

void vanilla::printError()
{
    perror(strerror(errno));
    exit(EXIT_FAILURE);
}