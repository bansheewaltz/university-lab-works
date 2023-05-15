#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_INTERNAL

#include "main.h"

void print_error(char *file, int line, char *error_msg) {
  char *executable_name = getenv("LAB");
  fprintf(stderr, "%s: %s:%d: %s\n", executable_name, file, line, error_msg);
}

void *safe_malloc(size_t size, char *file, int line) {
  void *pointer = malloc(size);
  if (pointer == NULL) {
    print_error(file, line, strerror(errno));
    exit(EXIT_FAILURE);
  }
  return pointer;
}

void *safe_calloc(size_t n, size_t size, char *file, int line) {
  void *pointer = calloc(n, size);
  if (pointer == NULL) {
    print_error(file, line, strerror(errno));
    exit(EXIT_FAILURE);
  }
  return pointer;
}
