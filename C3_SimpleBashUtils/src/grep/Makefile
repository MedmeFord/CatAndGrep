NAME = s21_grep
CC = gcc
CC_FLAGS = -Wall -Werror -Wextra -std=c11
SOURSES = s21_grep.c
OBJECTS = s21_grep.o

.PHONY: s21_grep

all: $(NAME)

s21_grep: $(OBJECTS)
	$(CC) $(OBJECTS) -o s21_grep

s21_grep.o: s21_grep.c
	$(CC) $(CC_FLAGS) -c s21_grep.c -g

clean:
	rm -rf *.o s21_grep a.out

test: s21_grep
	sh run.sh

test_line:
	./s21_grep -e int s21_grep.c

lo:
	for i in `seq 200 $(OP)`;	do sh run.sh; done;

lik: s21_grep
	leaks --atExit -- ./s21_grep -e int s21_grep.c -benst test_file/all_flag_tests/*

check: s21_grep
	cppcheck --enable=all --suppress=missingIncludeSystem . *.c *.h
	cp ../../materials/linters/CPPLINT.cfg ./
	python3 ./../../materials/linters/cpplint.py --extensions=c *.c *.h
	rm -f CPPLINT.cfg