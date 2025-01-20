test_that("rc_0() does not leak", {
  skip_without_valgrind()
  expect_no_leaks(.Call(rc_0))
})

test_that("rc_1() leaks", {
  skip_without_valgrind()
  expect_leak(.Call(rc_1), "rc_1")
})

test_that("rc_2() leaks", {
  skip_without_valgrind()
  expect_leak(.Call(rc_2), "rc_2")
})

test_that("rc_3() does not leak", {
  skip_without_valgrind()
  expect_no_leaks(.Call(rc_3))
})

test_that("rc_4() leaks", {
  skip_without_valgrind()
  expect_leak(
    tryCatch(.Call(rc_4), error = function(...) NULL),
    "rc_4"
  )
})
