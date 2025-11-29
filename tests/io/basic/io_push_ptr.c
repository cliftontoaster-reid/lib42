/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_push_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:00:00 by lfiorell           #+#    #+# */
/*   Updated: 2025/11/29 20:20:03 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
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

Test(io_push_ptr, null_pointer) {
  int fds[2];
  char out[4] = {0};

  cr_assert_eq(pipe(fds), 0);
  ssize_t wrote = io_push_ptr(fds[1], NULL, false);
  cr_assert_eq(wrote, 3);
  close(fds[1]);
  ssize_t r = read_from_fd(fds[0], out, 3);
  cr_assert_eq(r, 3);
  cr_assert_str_eq(out, "0x0");
  close(fds[0]);
}

Test(io_push_ptr, pointer_lowercase) {
  int fds[2];
  char out[32] = {0};
  void* p = (void*)(uintptr_t)0x1234;

  cr_assert_eq(pipe(fds), 0);
  ssize_t wrote = io_push_ptr(fds[1], p, false);
  const char* expected = "0x1234";
  cr_assert_eq(wrote, (ssize_t)strlen(expected));
  // Let's read actual number of bytes
  close(fds[1]);
  ssize_t r = read_from_fd(fds[0], out, strlen(expected));
  cr_assert_eq(r, (ssize_t)strlen(expected));
  cr_assert_str_eq(out, expected);
  close(fds[0]);
}

Test(io_push_ptr, pointer_uppercase) {
  int fds[2];
  char out[32] = {0};
  void* p = (void*)(uintptr_t)0xABCD;

  cr_assert_eq(pipe(fds), 0);
  ssize_t wrote = io_push_ptr(fds[1], p, true);
  cr_assert_gt(wrote, 0);
  close(fds[1]);
  ssize_t r = read_from_fd(fds[0], out, 6);
  cr_assert_eq(r, (ssize_t)6);
  cr_assert_str_eq(out, "0xABCD");
  close(fds[0]);
}
