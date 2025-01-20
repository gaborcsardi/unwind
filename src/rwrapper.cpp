#define R_NO_REMAP
#include <R.h>
#include <R_ext/Rdynload.h>

#include "rwrapper.h"

extern "C" {

static const R_CallMethodDef callMethods[]  = {
  { "vg_is_on",                (DL_FUNC) vg_is_on,                0 },
  { "vg_do_leak_check",        (DL_FUNC) vg_do_leak_check,        0 },
  { "vg_set_leak_check",       (DL_FUNC) vg_set_leak_check,       1 },
  { "vg_set_gen_suppressions", (DL_FUNC) vg_set_gen_suppressions, 1 },
  { "rc_0",                    (DL_FUNC) rc_0,                    0 },
  { "rc_1",                    (DL_FUNC) rc_1,                    0 },
  { "rc_2",                    (DL_FUNC) rc_2,                    0 },
  { "rc_3",                    (DL_FUNC) rc_3,                    0 },
  { "rc_4",                    (DL_FUNC) rc_4,                    0 },
  { NULL, NULL, 0 }
};

void R_init_unwind(DllInfo *dll) {
  R_registerRoutines(dll, NULL, callMethods, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
  R_forceSymbols(dll, TRUE);
}

} // extern "C"
