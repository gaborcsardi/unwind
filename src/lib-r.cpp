#include <vector>
#include <string>
#include <exception>
#include <stdlib.h>
#include <cstring>
#include <stdexcept>

#include "unwind.h"

extern "C" {

// all is well
SEXP rc_0() noexcept {
  char *x = (char*) malloc(100);
  free(x);
  return Rf_ScalarInteger(0);
}

// all good because the C++ function is converted to an R error
void rc_5_1() noexcept {
  char errmsg_[4096];
  try {
    std::vector<int> vec(20);
    vec[0] = 1;
    return;
  } catch(const std::exception &ex) {
    strncpy(errmsg_, ex.what(), sizeof(errmsg_) - 1);
    errmsg_[sizeof(errmsg_) - 1] = '\0';
  } catch(const std::string &ex) {
    strncpy(errmsg_, ex.c_str(), sizeof(errmsg_) - 1);
    errmsg_[sizeof(errmsg_) - 1] = '\0';
  } catch(...) {
    snprintf(errmsg_, sizeof(errmsg_) - 1, "unwind error");
    errmsg_[sizeof(errmsg_) - 1] = '\0';
  }
  Rf_error("%s", errmsg_);
}

SEXP rc_5() noexcept {
  rc_5_1();
  Rf_error("oops");
  return Rf_ScalarInteger(4);
}

// Similar to rc_5, but we use the macro.
// So for C++ functions that are called from R/C functions, I need to use
// CPP_BEGIN + CPP_END
void rc_6_1() noexcept {
CPP_BEGIN;
  std::vector<int> vec(20);
  vec[0] = 1;
  return;
CPP_END;
}

SEXP rc_6() noexcept {
  rc_6_1();
  Rf_error("oops");
  return Rf_ScalarInteger(4);
}

// Throwing an exception from rc_8_1 function is OK, because CPP_END
// converts it to an R error, and the trycatch scope makes sure that
// the vector object is cleaned up before that happens.
void rc_8_1() noexcept {
CPP_BEGIN;
  std::vector<int> vec(20);
  vec[0] = 1;
  throw std::runtime_error("this is good");
CPP_END;
}

SEXP rc_8() noexcept {
  rc_8_1();
  Rf_error("oops");
  return Rf_ScalarInteger(4);
}

// This is also OK, similar to rc_8, but rc_9_1 is a CPP function now.
// This is better, because rc_9_1() can be also called from a CPP function.
void rc_9_1() {
  std::vector<int> vec(20);
  vec[0] = 1;
  throw std::runtime_error("this is good");
}

SEXP rc_9() noexcept {
CPP_BEGIN
  rc_9_1();
CPP_END
  Rf_error("oops");
  return Rf_ScalarInteger(4);
}

// Calling an R/C function from a CPP in unwind_protect is OK.
void rc_11_2() {
  r_call([]() { Rf_error("oh-oh"); });
}

void rc_11_1() {
  std::vector<int> vec(20);
  vec[0] = 1;
  rc_11_2();
}

SEXP rc_11() noexcept {
CPP_BEGIN
  rc_11_1();
CPP_END
  return Rf_ScalarInteger(4);
}

// r_call test
void rc_12_2(SEXP v) noexcept {
  for (R_xlen_t i = 0; i < Rf_length(v); i++) {
    INTEGER(v)[i] = i + 1;
  }
}

void rc_12_1(SEXP v) {
  r_call([v]() { rc_12_2(v); });
}

SEXP rc_12() noexcept {
  SEXP ret = PROTECT(Rf_allocVector(INTSXP, 10));
CPP_BEGIN
  rc_12_1(ret);
CPP_END
  UNPROTECT(1);
  return ret;
}

// BAD STUFF, DON'T DO THESE ----------------------------------------------

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
// this does not leak, but it is still risky to use std containers in
// R/C code, because R API calls may error, see `rc_4()`.
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

// Calling R API (or R/C functions) from CPP functions is not OK
void rc_7_1() noexcept {
CPP_BEGIN;
  std::vector<int> vec(20);
  vec[0] = 1;
  Rf_error("oops2");
  return;
CPP_END;
}

SEXP rc_7() noexcept {
  rc_7_1();
  Rf_error("oops");
  return Rf_ScalarInteger(4);
}

// Calling an R/C function from a CPP function is not OK, may leak
void rc_10_2() noexcept {
  Rf_error("oh-oh");
}

void rc_10_1() noexcept {
  std::vector<int> vec(20);
  vec[0] = 1;
  rc_10_2();
  return;
}

SEXP rc_10() noexcept {
CPP_BEGIN
  rc_10_1();
CPP_END
  Rf_error("oops");
  return Rf_ScalarInteger(4);
}

} // extern "C"
