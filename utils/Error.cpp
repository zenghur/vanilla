// Copyright (c) 2016 zenghur

#include "Error.h"

#include <string.h>
#include <unistd.h>
#include <sys/errno.h>
#include <stdlib.h>

void vanilla::printError(std::string reason) {
  perror(reason.c_str());
  exit(EXIT_FAILURE);
}

// pthread functions don't set errno.
void vanilla::threadError(int status) {
  fprintf(stderr, "error %d:  %s\n", status, strerror(status));
  exit(EXIT_FAILURE);
}