#include "common.h"

int isDir(const char *fileName) {
  int exists = 1;
  FILE *file;
  file = fopen(fileName, "r");
  if (file != NULL)
    fclose(fileName);
  else
    exists = 0;
  return file == NULL;
}