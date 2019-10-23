#include "score.h"
#include <stdio.h>

int fails = 0;

void add_fail() {
  fails++;
}

int has_failed(int ir) {
  if (ir < 300) {
    return 1;
  }
  return 0;
}

int get_fails() {
  return fails;
}
