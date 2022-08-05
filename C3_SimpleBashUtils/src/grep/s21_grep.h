#ifndef CAT_C3_SIMPLEBASHUTILS_0_SRC_GREP_S21_GREP_H_
#define CAT_C3_SIMPLEBASHUTILS_0_SRC_GREP_S21_GREP_H_

#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
} Flag;

typedef struct {
  char name[BUFSIZ];
} Param;

void check_options(int argc, char *argv[], Flag options, Param *parametrs);
void make_regex(char *name, Flag options, Param *parametrs, int l, int n);
int check_flags(char *argv[], Flag *options, int argc);

#endif  // CAT_C3_SIMPLEBASHUTILS_0_SRC_GREP_S21_GREP_H_
