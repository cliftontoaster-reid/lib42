/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_push_ncstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:00:00 by lfiorell           #+#    #+# */
/*   Updated: 2025/11/29 20:20:03 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
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

Test(io_push_ncstr, n_less_than_len) {
  int fds[2];
  char out[4] = {0};
  const char* s = "abcd";  // len = 4

  cr_assert_eq(pipe(fds), 0);
  ssize_t wrote = io_push_ncstr(fds[1], s, 2);
  cr_assert_eq(wrote, 2);
  close(fds[1]);
  ssize_t r = read_from_fd(fds[0], out, 2);
  cr_assert_eq(r, 2);
  cr_assert_str_eq(out, "ab");
  close(fds[0]);
}

Test(io_push_ncstr, n_more_than_len) {
  int fds[2];
  char out[6] = {0};
  const char* s = "xyz";  // len = 3

  cr_assert_eq(pipe(fds), 0);
  ssize_t wrote = io_push_ncstr(fds[1], s, 10);
  cr_assert_eq(wrote, 3);
  close(fds[1]);
  ssize_t r = read_from_fd(fds[0], out, 3);
  cr_assert_eq(r, 3);
  cr_assert_str_eq(out, "xyz");
  close(fds[0]);
}

Test(io_push_ncstr, n_equals_len) {
  int fds[2];
  char out[5] = {0};
  const char* s = "test";

  cr_assert_eq(pipe(fds), 0);
  ssize_t wrote = io_push_ncstr(fds[1], s, 4);
  cr_assert_eq(wrote, 4);
  close(fds[1]);
  ssize_t r = read_from_fd(fds[0], out, 4);
  cr_assert_eq(r, 4);
  cr_assert_str_eq(out, "test");
  close(fds[0]);
}

Test(io_push_ncstr, n_zero) {
  int fds[2];
  const char* s = "hello";

  cr_assert_eq(pipe(fds), 0);
  ssize_t wrote = io_push_ncstr(fds[1], s, 0);
  cr_assert_eq(wrote, 0);
  close(fds[1]);
  close(fds[0]);
}
