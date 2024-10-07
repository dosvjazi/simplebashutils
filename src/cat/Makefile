CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
FILE = s21_cat
SOURCE0 = ../common/common.c
SOURCE1 = cat.c

all: s21_cat

s21_cat:
	$(CC) $(CFLAGS) $(SOURCE0) $(SOURCE1) -o $(FILE)

rebuild:
	make clean
	make all

clean:
	rm -rf $(FILE)