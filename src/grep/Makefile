CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
FILE = s21_grep
SOURCE0 = ../common/common.c
SOURCE1 = grep.c

all: s21_grep

s21_grep:
	$(CC) $(CFLAGS) $(SOURCE0) $(SOURCE1) -o $(FILE)

rebuild:
	make clean
	make all

clean:
	rm -rf $(FILE)