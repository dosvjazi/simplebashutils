#ifndef GREP_H
#define GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>

#include "../common/common.h"

#define SIZE 1024

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int empty;
  int pattern;
  int multiple;
  int error;
} flags;

void parse(int argc, char *argv[], flags *flags, const char *short_options,
           const struct option *long_options, char patterns[SIZE * SIZE]);
void grep(const char *filename, flags flags, char patterns[SIZE * SIZE]);
int print(const char *filename, char *line, flags flags, int *matched_number,
          int line_number, regex_t *re, int running);
void read_line(FILE *file, char line[SIZE]);
void print_matched(regex_t *re, char *line, const flags flags,
                   const char *filename, int line_number);
int read_file(char *filename, char patterns[SIZE * SIZE]);

#endif