#ifndef MAIN_H_
#define MAIN_H_

#include <stdbool.h>

#define VERTICES_MAX_COUNT 5000

typedef unsigned int uint;
typedef struct {
  int vertices_count;
  int edges_count;
  uint *graph_array;
} Graph;

typedef struct {
  int *stack_array;
  int stack_top;
  int stack_capacity;
} Stack;

#endif  // MAIN_H_
