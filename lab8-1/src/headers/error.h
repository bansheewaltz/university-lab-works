#ifndef ERROR_H_
#define ERROR_H_

#include <stdbool.h>

typedef enum
{
  E_SUCCESS,
  E_BAD_VERTEX,
  E_BAD_LENGTH,
  E_BAD_INPUT_FORMAT,
  E_BAD_NUMBER_OF_VERTICES,
  E_BAD_NUMBER_OF_EDGES,
  E_BAD_NUMBER_OF_LINES,
  E_NO_SPANNING_TREE,
  E_MEMORY_ALLOCATION_FAIL
} ReturnCode;

void print_error_message(ReturnCode return_code);
void print_error_message_if_any(ReturnCode return_code);
bool is_error(ReturnCode result);

#endif  // ERROR_H_
