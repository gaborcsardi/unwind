#ifndef UNWIND_RWRAPPER_H
#define UNWIND_RWRAPPER_H

// C++ functions (internal) -----------------------------------------------
void cpp_1();

// R/C functions ----------------------------------------------------------
#include <Rinternals.h>
extern "C" {

// -- public API -----------
SEXP vg_is_on();
SEXP vg_do_leak_check();
SEXP vg_set_leak_check(SEXP val);
SEXP vg_set_gen_suppressions(SEXP val);

SEXP rc_0() noexcept;
SEXP rc_1() noexcept;
SEXP rc_2() noexcept;
SEXP rc_3() noexcept;
SEXP rc_4() noexcept;
SEXP rc_5() noexcept;
SEXP rc_6() noexcept;
SEXP rc_7() noexcept;
SEXP rc_8() noexcept;
SEXP rc_9() noexcept;
SEXP rc_10() noexcept;
SEXP rc_11() noexcept;
SEXP rc_12() noexcept;

// -- internl API ----------

} // extern "C" -----------------------------------------------------------

#endif // UNWIND_RWRAPPER_H
