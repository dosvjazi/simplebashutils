#include "cat.h"

int main(int argc, char *argv[]) {
  flags flags = {0};
  const char *short_options = "AbeEnstTv";
  const struct option long_options[] = {
      {"show-all", no_argument, NULL, 'A'},
      {"number-nonblank", no_argument, NULL, 'b'},
      {"show-ends", no_argument, NULL, 'E'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {"show-tabs", no_argument, NULL, 'T'},
      {"show-nonprinting", no_argument, NULL, 'v'},
      {NULL, 0, NULL, 0}};
  parse(argc, argv, &flags, short_options, long_options);
  if (flags.error == 0) {
    for (int i = optind; i < argc; i++) {
      if (isDir(argv[i]) == 1)
        cat(argv[i], flags);
      else
        printf("cat: %s: No such file or directory\n", argv[i]);
    }
  } else
    printf("cat: Invalid option(s). Aborting..\n");
  return 0;
}

void parse(int argc, char *argv[], flags *flags, const char *short_options,
           const struct option *long_options) {
  opterr = 0;
  int option_index;
  int result;
  while ((result = getopt_long(argc, argv, short_options, long_options,
                               &option_index)) != -1) {
    if (result == 'A') {
      flags->E = flags->T = flags->v = 1;
    } else if (result == 'b') {
      flags->b = 1;
      if (flags->n == 1) flags->n = 0;
    } else if (result == 'e') {
      flags->v = flags->E = 1;
    } else if (result == 'E') {
      flags->E = 1;
    } else if (result == 'n') {
      if (flags->b == 0) flags->n = 1;
    } else if (result == 's') {
      flags->s = 1;
    } else if (result == 't') {
      flags->v = flags->T = 1;
    } else if (result == 'T') {
      flags->T = 1;
    } else if (result == 'v') {
      flags->v = 1;
    } else if (result == '?') {
      flags->error = 1;
    }
  }
  if (argc - optind == 0) flags->error = 1;
}

void cat(const char *filename, const flags flags) {
  FILE *file;
  file = fopen(filename, "r");
  int count = 1, newline = 1, squeeze = 0, ch;
  while ((ch = fgetc(file)) != EOF) {
    if (flags.b && newline && ch != '\n') printf("%*d\t", 6, count++);
    if (flags.E && ch == '\n' && !squeeze) {
      if ((flags.n || flags.b) && newline)
        printf("%*c ", 8, '$');
      else
        putchar('$');
    }
    if (flags.n && newline && !squeeze) printf("%*d\t", 6, count++);
    if (flags.s) {
      if (newline && ch == '\n' && squeeze) {
        ch = '\0';
      } else if (newline && ch == '\n' && !squeeze) {
        putchar('\n');
        squeeze = 1;
      } else if (ch != '\n') {
        squeeze = 0;
      }
    }
    if (flags.T && ch == '\t') {
      putchar('^');
      ch = 'I';
    }
    if (flags.v) {
      if (ch >= 0 && ch <= 31 && ch != '\t' && ch != '\n') {
        putchar('^');
        ch += 64;
      } else if (ch == 127) {
        putchar('^');
        ch = '?';
      } else if (ch >= 128 && ch <= 159) {
        printf("M-^");
        ch -= 64;
      } else if (ch >= 160 && ch <= 254) {
        printf("M-");
        ch -= 128;
      } else if (ch == 255) {
        printf("M-^");
        ch = '?';
      }
    }
    if (!squeeze) putchar(ch);
    newline = ch == '\n' ? 1 : 0;
  }
  fclose(file);
}