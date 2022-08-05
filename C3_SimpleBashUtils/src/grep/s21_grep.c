#include "s21_grep.h"

int main(int argc, char *argv[]) {
  if (argc > 1) {
    Flag options = {0};
    Param parametrs[BUFSIZ];
    if (check_flags(argv, &options, argc) == 0) {
      check_options(argc, argv, options, parametrs);
    }
  }
  return 0;
}

void check_options(int argc, char *argv[], Flag options, Param *parametrs) {
  int n = 0;
  if (argv[1][0] != '-') {
    strcpy(parametrs[0].name, argv[1]);
    for (int i = 2; i < argc; i++) {
      make_regex(argv[i], options, parametrs, argc, n);
    }
  } else {
    int k = 0;
    int flag = 0;
    char str[BUFSIZ] = {'\0'}, name[BUFSIZ] = {'\0'};
    FILE *file;
    for (int i = 1; i < argc; i++) {
      if (argv[i][0] == '-') {
        if (options.f) {
          strcpy(name, argv[2]);
          if ((file = fopen(name, "r")) == NULL) {
            if (!options.s)
              printf("s21_grep: %s: No such file or directory\n", argv[2]);
          } else {
            while (fgets(str, BUFSIZ - 1, file) != NULL) {
              int len = strlen(str);
              if (str[len - 1] == '\n') str[len - 1] = '\0';
              strcpy(parametrs[n].name, str);
              n++;
            }
            k = i;
            fclose(file);
          }
        } else {
          if (options.e && !options.i && !options.v && !options.c &&
              !options.l && !options.n && !options.h && !options.s &&
              !options.o)
            flag = 0;
          if (flag == 0) {
            strcpy(parametrs[n].name, argv[i + 1]);
            n++;
            flag = 1;
          }
          k += 1;
          if (n > 1) k += 1;
        }
      }
    }
    for (int i = k + 2; i < argc; i++) {
      int l = argc - (k + 2);
      make_regex(argv[i], options, parametrs, l, n);
    }
  }
}

void make_regex(char *name, Flag options, Param *parametrs, int l, int n) {
  FILE *fp;
  regex_t regex;
  if ((fp = fopen(name, "r")) == NULL) {
    if (!options.s) printf("s21_grep: %s: No such file or directory\n", name);
  } else {
    int fail_or_success, count = 0, number = 1;
    char str[BUFSIZ] = {'\0'};
    int regflag = 0;
    if (options.i) regflag = REG_ICASE;
    while (fgets(str, BUFSIZ - 1, fp) != NULL) {
      for (int i = 0; i < n; i++) {
        regcomp(&regex, parametrs[i].name, regflag);
        fail_or_success = regexec(&regex, str, 0, NULL, 0);
        regfree(&regex);
        if (!fail_or_success) {
          break;
        }
      }
      if (!fail_or_success) count++;
      if (!options.c && options.v && fail_or_success == 1) printf("%s", str);
      if (!options.l && !options.c && !options.v && fail_or_success == 0) {
        if (l >= 2 && !options.h) printf("%s:", name);
        if (options.n) printf("%d:", number);
        if (options.o) {
          printf("%s\n", parametrs[0].name);
        } else {
          printf("%s", str);
        }
      }
      if (options.l && fail_or_success == 0) {
        printf("%s\n", name);
        break;
      }
      fail_or_success = 1;
      number++;
    }
    if (options.c) printf("%d\n", count);
    fclose(fp);
  }
}

int check_flags(char *argv[], Flag *options, int argc) {
  int error = 0;
  for (int j = 1; j < argc; j++) {
    if (argv[j][0] == '-' && argv[j][1] != '-') {
      int i = 1;
      while (argv[j][i] != '\0') {
        if (argv[j][i] == 'e') {
          options->e = 1;
        } else if (argv[j][i] == 'i') {
          options->i = 1;
        } else if (argv[j][i] == 'v') {
          options->v = 1;
        } else if (argv[j][i] == 'c') {
          options->c = 1;
        } else if (argv[j][i] == 'l') {
          options->l = 1;
        } else if (argv[j][i] == 'n') {
          options->n = 1;
        } else if (argv[j][i] == 'h') {
          options->h = 1;
        } else if (argv[j][i] == 's') {
          options->s = 1;
        } else if (argv[j][i] == 'f') {
          options->f = 1;
        } else if (argv[j][i] == 'o') {
          options->o = 1;
        } else {
          printf("error");
          error = 1;
          break;
        }
        i++;
      }
    }
  }
  return error;
}
