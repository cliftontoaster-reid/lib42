/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_push_uint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:00:00 by lfiorell           #+#    #+# */
/*   Updated: 2025/11/29 20:20:03 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <limits.h>
#include <stdint.h>
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

Test(io_push_uint, write_zero) {
  int fds[2];
  char out[2] = {0};

  cr_assert_eq(pipe(fds), 0);
  ssize_t wrote = io_push_uint(fds[1], 0);
  cr_assert_eq(wrote, 1);
  close(fds[1]);
  ssize_t r = read_from_fd(fds[0], out, 1);
  cr_assert_eq(r, 1);
  cr_assert_str_eq(out, "0");
  close(fds[0]);
}

Test(io_push_uint, write_value) {
  int fds[2];
  char out[21] = {0};

  cr_assert_eq(pipe(fds), 0);
  ssize_t wrote = io_push_uint(fds[1], 1234567890ULL);
  cr_assert_eq(wrote, (ssize_t)strlen("1234567890"));
  close(fds[1]);
  ssize_t r = read_from_fd(fds[0], out, strlen("1234567890"));
  cr_assert_eq(r, (ssize_t)strlen("1234567890"));
  cr_assert_str_eq(out, "1234567890");
  close(fds[0]);
}

Test(io_push_uint, write_uint64_max) {
  int fds[2];
  char out[64] = {0};
  const char* expected = "18446744073709551615";

  cr_assert_eq(pipe(fds), 0);
  ssize_t wrote = io_push_uint(fds[1], UINT64_MAX);
  cr_assert_eq(wrote, (ssize_t)strlen(expected));
  close(fds[1]);
  ssize_t r = read_from_fd(fds[0], out, strlen(expected));
  cr_assert_eq(r, (ssize_t)strlen(expected));
  cr_assert_str_eq(out, expected);
  close(fds[0]);
}
