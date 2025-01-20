expect_no_leaks <- function(expr, ...) {
  # Generate suppressions, in case there are leaks that we want suppressed
  .Call(vg_set_gen_suppressions, "all")
  vg_res <- with_valgrind(expr)
  if (!vg_res$valgrind_on) {
    testthat::expect(FALSE, "Valgrind is off", ...)
  } else if (length(vg_res$valgrind_output) == 0) {
    testthat::expect(TRUE, "No leaks, good", ...)
  } else {
    msg <- paste(
      c("Memory leak detected", vg_res$valgrind_output),
      collapse = "\n"
    )
    testthat::expect(FALSE, msg, ...)
  }
}

expect_leak <- function(expr, leaky_fun, info = NULL, ...) {
  vg_res <- with_valgrind(expr)
  if (!vg_res$valgrind_on) {
    testthat::expect(FALSE, "Valgrind is off", info = info, ...)
  } else if (length(vg_res$valgrind_output) == 0) {
    testthat::expect(FALSE, "No leaks, expected at least one.", info = info, ...)
  } else {
    re <- paste0("^==[0-9]+== +by 0x[0-9A-F]+: ", leaky_fun, " ")
    if (any(grepl(re, vg_res$valgrind_output))) {
      testthat::expect(TRUE, paste0(leaky_fun, " indeed leaks"), info = info, ...)
    } else {
      testthat::expect(
        FALSE,
        paste0(leaky_fun, " does not leak (but others do)"),
        info = info %||% paste(vg_res$valgrind_output, collapse = "\n")
      )
    }
  }
}

valgrind_is_on <- function() {
  .Call(vg_is_on)
}

skip_without_valgrind <- function() {
  if (Sys.getenv("VALGRIND_FORCE") != "true" && !valgrind_is_on()) {
    testthat::skip("No Valgrind")
  }
}

with_valgrind <- function(expr) {
  if (!valgrind_is_on()) {
    list(
      value = force(expr),
      valgrind_on = FALSE,
      valgrind_output = NULL
    )

  } else {
    logfile <- Sys.getenv("VALGRIND_LOG", "/tmp/valgrind.log")
    if (!file.exists(logfile)) {
      stop(
        "Valgrind log file does not exist. Set VALGRIND_LOG, or ",
        "use --log-file=/tmp/valgrind.log for the default log file."
      )
    }
    pos <- file.size(logfile)
    value <- force(expr)
    .Call(vg_do_leak_check)
    list(
      value = value,
      valgrind_on = TRUE,
      valgrind_output = read_lines(logfile, skip_bytes = pos)
    )
  }
}

read_lines <- function(path, skip_bytes = 0L) {
  con <- file(path, open = "rb")
  on.exit(close(con), add = TRUE)
  if (skip_bytes > 0) {
    readBin(con, what = "raw", n = skip_bytes)
  }
  readLines(con)
}

`%||%` <- function(l, r) {
  if (is.null(l)) {
    r
  } else {
    l
  }
}