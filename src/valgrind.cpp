#include <string.h>
#include <Rinternals.h>
#include "valgrind.h"
#include "memcheck.h"

extern "C" {

SEXP vg_do_leak_check() {
  VALGRIND_DO_ADDED_LEAK_CHECK;
  return R_NilValue;
}

SEXP vg_is_on() {
  if (RUNNING_ON_VALGRIND == 1) {
    return Rf_ScalarLogical(1);
  } else {
    return Rf_ScalarLogical(0);
  }
}

SEXP vg_set_leak_check(SEXP val) {
  if (RUNNING_ON_VALGRIND == 1) {
    const char *cval = CHAR(STRING_ELT(val, 0));
    if (!strcmp("yes", cval)) {
      VALGRIND_CLO_CHANGE("--leak-check=yes");
    } else if (!strcmp("no", cval)) {
      VALGRIND_CLO_CHANGE("--leak-check=no");
    } else if (!strcmp("summary", cval)) {
      VALGRIND_CLO_CHANGE("--leak-check=summary");
    } else if (!strcmp("full", cval)) {
      VALGRIND_CLO_CHANGE("--leak-check=full");
    } else {
      Rf_error("Invalid --leak-check option for Valgrind");
    }
  }
  return R_NilValue;
}

SEXP vg_set_gen_suppressions(SEXP val) {
  if (RUNNING_ON_VALGRIND == 1) {
    const char *cval = CHAR(STRING_ELT(val, 0));
    if (!strcmp("yes", cval)) {
      VALGRIND_CLO_CHANGE("--gen-suppressions=yes");
    } else if (!strcmp("no", cval)) {
      VALGRIND_CLO_CHANGE("--gen-suppressions=no");
    } else if (!strcmp("all", cval)) {
      VALGRIND_CLO_CHANGE("--gen-suppressions=all");
    } else {
      Rf_error("Invalid --gen-suppressions option for Valgrind");
    }
  }
  return R_NilValue;
}

} // extern "C"
