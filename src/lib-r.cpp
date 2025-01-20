#include <vector>
#include <stdlib.h>
#include <Rinternals.h>

extern "C" {

// all is well
SEXP rc_0() noexcept {
  char *x = (char*) malloc(100);
  free(x);
  return Rf_ScalarInteger(0);
}

// simple memory leak
SEXP rc_1() noexcept {
  char *x = (char*) malloc(100);
  x[0] = '\0';
  return Rf_ScalarInteger(1);
}

// memory leak from C++
SEXP rc_2() noexcept {
  char *v = new char[50];
  v[0] = '\0';
  return Rf_ScalarInteger(2);
}

// no memory leak from the container
SEXP rc_3() noexcept {
  std::vector<int> vec(20);
  vec[0] = 1;
  return Rf_ScalarInteger(3);
}

// memory leak from the container + R error
SEXP rc_4() noexcept {
  std::vector<int> vec(20);
  vec[0] = 1;
  Rf_error("oops");
  return Rf_ScalarInteger(4);
}

} // extern "C"
