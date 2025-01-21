test_that("rc_0() does not leak", {
  skip_without_valgrind()
  expect_no_leaks(.Call(rc_0))
})

test_that("rc_0 works", {
  expect_equal(.Call(rc_0), 0L)
})

test_that("rc_1() leaks", {
  skip_without_valgrind()
  expect_leak(.Call(rc_1), "rc_1")
})

test_that("rc_1 works", {
  expect_equal(.Call(rc_1), 1L)
})

test_that("rc_2() leaks", {
  skip_without_valgrind()
  expect_leak(.Call(rc_2), "rc_2")
})

test_that("rc_2 works", {
  expect_equal(.Call(rc_2), 2L)
})

test_that("rc_3() does not leak", {
  skip_without_valgrind()
  expect_no_leaks(.Call(rc_3))
})

test_that("rc_3 works", {
  expect_equal(.Call(rc_3), 3L)
})

test_that("rc_4() leaks", {
  skip_without_valgrind()
  expect_leak(
    tryCatch(.Call(rc_4), error = function(...) NULL),
    "rc_4"
  )
})

test_that("rc_4 works", {
  expect_snapshot(error = TRUE, .Call(rc_4))
})

test_that("rc_5() does not leak", {
  skip_without_valgrind()
  expect_no_leaks(try(.Call(rc_5), silent = TRUE))
})

test_that("rc_5 works", {
  expect_snapshot(error = TRUE, .Call(rc_5))
})

test_that("rc_6() does not leak", {
  skip_without_valgrind()
  expect_no_leaks(try(.Call(rc_6), silent = TRUE))
})

test_that("rc_6 works", {
  expect_snapshot(error = TRUE, .Call(rc_6))
})

test_that("rc_7() leaks", {
  skip_without_valgrind()
  expect_leak(
    tryCatch(.Call(rc_7), error = function(...) NULL),
    "rc_7"
  )
})

test_that("rc_7 works", {
  expect_snapshot(error = TRUE, .Call(rc_7))
})

test_that("rc_8() does not leak", {
  skip_without_valgrind()
  expect_no_leaks(try(.Call(rc_8), silent = TRUE))
})

test_that("rc_8 works", {
  expect_snapshot(error = TRUE, .Call(rc_8))
})

test_that("rc_9() does not leak", {
  skip_without_valgrind()
  expect_no_leaks(try(.Call(rc_9), silent = TRUE))
})

test_that("rc_9 works", {
  expect_snapshot(error = TRUE, .Call(rc_9))
})

test_that("rc_10() leaks", {
  skip_without_valgrind()
  expect_leak(
    tryCatch(.Call(rc_10), error = function(...) NULL),
    "rc_10"
  )
})

test_that("rc_10 works", {
  expect_snapshot(error = TRUE, .Call(rc_10))
})

test_that("rc_11() does not leak", {
  skip_without_valgrind()
  expect_no_leaks(try(.Call(rc_11), silent = TRUE))
})

test_that("rc_11 works", {
  expect_snapshot(error = TRUE, .Call(rc_11))
})

test_that("rc_12() does not leak", {
  skip_without_valgrind()
  expect_no_leaks(.Call(rc_12))
})

test_that("rc_12() is correct", {
  expect_equal(.Call(rc_12), 1:10)
})
