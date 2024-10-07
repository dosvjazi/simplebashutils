#ifndef CAT_H
#define CAT_H

#include <getopt.h>
#include <stdio.h>

#include "../common/common.h"

typedef struct {
  int b;
  int E;
  int n;
  int s;
  int T;
  int v;
  int error;
} flags;

void parse(int argc, char *argv[], flags *flags, const char *short_options,
           const struct option *long_options);
void cat(const char *filename, flags flags);

#endif