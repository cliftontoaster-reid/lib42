/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_push_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:00:00 by lfiorell           #+#    #+# */
/*   Updated: 2025/11/29 20:20:03 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

#include "42/io/basic.h"

static ssize_t read_from_fd(int fd, void* buf, size_t len) {
  ssize_t r = 0;
  ssize_t ret;
  char* p = (char*)buf;
  while ((size_t)r < len && (ret = read(fd, p + r, len - r)) > 0) r += ret;
  return r;
}

Test(io_push_double, write_zero_precision_2) {
  int fds[2];
  char out[5] = {0};

  cr_assert_eq(pipe(fds), 0);
  ssize_t wrote = io_push_double(fds[1], 0.0, 2);
  cr_assert_eq(wrote, 4);  // 0.00
  close(fds[1]);
  ssize_t r = read_from_fd(fds[0], out, 4);
  cr_assert_eq(r, 4);
  cr_assert_str_eq(out, "0.00");
  close(fds[0]);
}

Test(io_push_double, write_positive) {
  int fds[2];
  char out[16] = {0};

  cr_assert_eq(pipe(fds), 0);
  ssize_t wrote = io_push_double(fds[1], 12.3456, 3);
  cr_assert_gt(wrote, 0);
  close(fds[1]);
  ssize_t r = read_from_fd(fds[0], out, 8);
  cr_assert_gt(r, 0);
  // Accept rounding to 12.346
  cr_assert_str_eq(out, "12.346");
  close(fds[0]);
}

Test(io_push_double, write_negative) {
  int fds[2];
  char out[16] = {0};

  cr_assert_eq(pipe(fds), 0);
  ssize_t wrote = io_push_double(fds[1], -1.25, 2);
  cr_assert_gt(wrote, 0);
  close(fds[1]);
  ssize_t r = read_from_fd(fds[0], out, 5);
  cr_assert_gt(r, 0);
  cr_assert_str_eq(out, "-1.25");
  close(fds[0]);
}

Test(io_push_double, write_nan) {
  int fds[2];
  char out[4] = {0};

  cr_assert_eq(pipe(fds), 0);
  ssize_t wrote = io_push_double(fds[1], NAN, 2);
  cr_assert_eq(wrote, 3);
  close(fds[1]);
  ssize_t r = read_from_fd(fds[0], out, 3);
  cr_assert_eq(r, 3);
  cr_assert_str_eq(out, "nan");
  close(fds[0]);
}

Test(io_push_double, write_inf_and_minus_inf) {
  int fds[2];
  char out[5] = {0};

  cr_assert_eq(pipe(fds), 0);
  ssize_t wrote = io_push_double(fds[1], INFINITY, 2);
  cr_assert_eq(wrote, 3);
  close(fds[1]);
  ssize_t r = read_from_fd(fds[0], out, 3);
  cr_assert_eq(r, 3);
  cr_assert_str_eq(out, "inf");
  close(fds[0]);

  cr_assert_eq(pipe(fds), 0);
  wrote = io_push_double(fds[1], -INFINITY, 2);
  cr_assert_eq(wrote, 4);
  close(fds[1]);
  r = read_from_fd(fds[0], out, 4);
  cr_assert_eq(r, 4);
  cr_assert_str_eq(out, "-inf");
  close(fds[0]);
}

Test(io_push_double, rounding_overflow) {
  int fds[2];
  char out[10] = {0};

  cr_assert_eq(pipe(fds), 0);
  // 0.999 with precision 2 should become 1.00
  ssize_t wrote = io_push_double(fds[1], 0.999, 2);
  cr_assert_gt(wrote, 0);
  close(fds[1]);
  ssize_t r = read_from_fd(fds[0], out, 4);
  cr_assert_eq(r, 4);
  cr_assert_str_eq(out, "1.00");
  close(fds[0]);
}
