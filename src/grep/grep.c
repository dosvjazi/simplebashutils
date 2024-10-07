#include "grep.h"
// cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
int main(int argc, char *argv[]) {
  flags flags = {0};
  char patterns[SIZE * SIZE] = {0};
  const char *short_options = "e:ivclnhsf:o";
  const struct option long_options[] = {
      {"regexp", required_argument, NULL, 'e'},
      {"ignore-case", no_argument, NULL, 'i'},
      {"invert-match", no_argument, NULL, 'v'},
      {"count", no_argument, NULL, 'c'},
      {"files-with-match", no_argument, NULL, 'l'},
      {"no-filename", no_argument, NULL, 'h'},
      {"no-messages", no_argument, NULL, 's'},
      {"file", required_argument, NULL, 'f'},
      {"only-matching", no_argument, NULL, 'o'},
      {NULL, 0, NULL, 0}};
  parse(argc, argv, &flags, short_options, long_options, patterns);
  if (flags.error == 0) {
    if (flags.pattern) strcat(patterns, argv[optind]);
    for (int i = optind + flags.pattern; i < argc; i++) {
      if (isDir(argv[i]))
        grep(argv[i], flags, patterns);
      else if (!flags.s)
        printf("\ngrep: %s: No such file or directory\n", argv[i]);
    }
  } else if (flags.error == 1)
    printf("grep: Invalid option(s). Aborting..\n");
  return 0;
}

void parse(int argc, char *argv[], flags *flags, const char *short_options,
           const struct option *long_options, char patterns[SIZE * SIZE]) {
  opterr = 0;
  int option_index;
  int result;
  while ((result = getopt_long(argc, argv, short_options, long_options,
                               &option_index)) != -1 &&
         !flags->error) {
    if (result == 'e') {
      if (flags->e > 0 || flags->f - flags->empty > 0) strcat(patterns, "\\|");
      strcat(patterns, optarg);
      flags->e = flags->e + 1;
    }
    if (result == 'i') flags->i = 1;
    if (result == 'v') flags->v = 1;
    if (result == 'c') flags->c = 1;
    if (result == 'l') flags->l = 1;
    if (result == 'n') flags->n = 1;
    if (result == 'h') flags->h = 1;
    if (result == 's') flags->s = 1;
    if (result == 'f' && isDir(optarg)) {
      if (flags->e > 0 || flags->f - flags->empty > 0) strcat(patterns, "\\|");
      int empty = read_file(optarg, patterns);
      if (empty == 1) strcat(patterns, "\b\b");
      flags->empty += empty;
      flags->f = flags->f + 1;
    } else if (result == 'f' && !isDir(optarg))
      flags->error = 1;
    if (result == 'o') flags->o = 1;
    if (result == '?') flags->error = 1;
  }
  if (flags->f - flags->empty > 0 || flags->e > 0) flags->empty = 0;
  if (argc - optind == 0) flags->error = 1;
  if (argc - optind == 1 && flags->e == 0 && flags->f == 0) flags->error = 1;
  if (flags->e == 0 && flags->f == 0) flags->pattern = 1;
  if (flags->pattern && argc - optind > 2) flags->multiple = 1;
  if (!flags->pattern && argc - optind > 1) flags->multiple = 1;
  if (flags->empty > 0) patterns[0] = -1;
}

void grep(const char *filename, const flags flags, char patterns[SIZE * SIZE]) {
  FILE *file;
  file = fopen(filename, "r");
  int running = 1;
  int line_number = 0;
  int matched_number = 0;
  while (running) {
    char line[SIZE] = {0};
    read_line(file, line);
    int length = strlen(line);
    line_number++;
    if (line[length - 1] == EOF) {
      running = 0;
      line[length - 1] = '\n';
    }
    regex_t re;
    int igonre_case = flags.i ? REG_ICASE : 0;
    if (regcomp(&re, patterns, REG_NEWLINE | igonre_case) == 0) {
      running = print(filename, line, flags, &matched_number, line_number, &re,
                      running);
    } else {
      printf("grep: Bad regex. Aborting...\n");
      running = 0;
    }
    regfree(&re);
  }
  if (flags.c && !flags.l && (!flags.empty || flags.v)) {
    if (!flags.h && flags.multiple) printf("%s:", filename);
    printf("%d\n", matched_number);
  }
}

int print(const char *filename, char *line, flags flags, int *matched_number,
          int line_number, regex_t *re, int running) {
  int status = regexec(re, line, (size_t)0, NULL, 0) != 0 ? 0 : 1;
  if (flags.v) status = !status;
  if (status == 1) {
    *matched_number = *matched_number + 1;
    if (!flags.l && !flags.c && !flags.o) {
      if (flags.multiple && !flags.h) printf("%s:", filename);
      if (flags.n) printf("%d:", line_number);
      printf("%s", line);
    } else if (!flags.l && !flags.c && flags.o) {
      print_matched(re, line, flags, filename, line_number);
    } else if (flags.l && status) {
      printf("%s\n", filename);
      running = 0;
    }
  }
  return running;
}

void read_line(FILE *file, char line[SIZE]) {
  int length = 0;
  int ch;
  do {
    ch = fgetc(file);
    length++;
    line[length - 1] = ch;
  } while (ch != '\n' && ch != EOF);
}

void print_matched(regex_t *re, char *line, const flags flags,
                   const char *filename, int line_number) {
  regmatch_t pmatch[1];
  while (regexec(re, line, 1, pmatch, 0) == 0) {
    if (flags.multiple && !flags.h) printf("%s:", filename);
    if (flags.n) printf("%d:", line_number);
    for (int j = 0; j < pmatch->rm_eo; j++) {
      if (j >= pmatch->rm_so) printf("%c", line[j]);
      // temp[j] = 127;
      line[j] = 127;
    }
    printf("\n");
  }
}

int read_file(char *filename, char patterns[SIZE * SIZE]) {
  FILE *file;
  file = fopen(filename, "r");
  int running = 1;
  int once = 0;
  int empty = 0;
  while (running) {
    if (once) strcat(patterns, "\\|");
    char line[SIZE] = {0};
    read_line(file, line);
    int length = strlen(line);
    if (line[length - 1] == EOF) {
      line[length - 1] = '\n';
      running = 0;
      if (!once && length == 1) empty = 1;
    }
    if (line[length - 1] == '\n') line[length - 1] = 0;
    if (!empty) strcat(patterns, line);
    once = 1;
  }
  return empty;
}