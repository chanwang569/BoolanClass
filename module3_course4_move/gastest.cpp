#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// A simple case to show how gas usage. -fsanitize=address
int main() {
  char *x = (char*)malloc(10 * sizeof(char*));
  free(x);
  return x[5];
}