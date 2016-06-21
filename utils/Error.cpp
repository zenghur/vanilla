// Copyright (c) 2016 zenghur

#include "Error.h"

#include <string.h>
#include <unistd.h>
#include <sys/errno.h>
#include <stdlib.h>

void vanilla::printError(std::string reason) {
    if (reason.empty()) {
         perror(strerror(errno));
    } else {
        perror(reason.c_str());
    }
    exit(EXIT_FAILURE);
}