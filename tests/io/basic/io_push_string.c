/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_push_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:00:00 by lfiorell           #+#    #+# */
/*   Updated: 2025/11/29 20:20:03 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "42/alloc/string.h"
#include "42/io/basic.h"

static ssize_t read_from_fd(int fd, void* buf, size_t len) {
  ssize_t r = 0;
  ssize_t ret;
  char* p = (char*)buf;
  while ((size_t)r < len && (ret = read(fd, p + r, len - r)) > 0) r += ret;
  return r;
}

Test(io_push_string, write_t_string) {
  int fds[2];
  t_string* s = string_from("world");
  char out[6] = {0};

  cr_assert_not_null(s);
  fprintf(stderr, "[DEBUG] write_t_string: new string created, size=%zu\n",
          s->size);
  fflush(stderr);
  cr_assert_eq(pipe(fds), 0);
  fprintf(stderr, "[DEBUG] write_t_string: pipe created\n");
  fflush(stderr);
  ssize_t wrote;
  fprintf(stderr, "[DEBUG] write_t_string: about to write, size=%zu\n",
          s->size);
  fflush(stderr);
  wrote = io_push_string(fds[1], s);
  fprintf(stderr, "[DEBUG] write_t_string: wrote returned %zd\n", wrote);
  fflush(stderr);
  cr_assert_eq(wrote, (ssize_t)s->size);
  close(fds[1]);
  ssize_t r = read_from_fd(fds[0], out, s->size);
  cr_assert_eq(r, (ssize_t)s->size);
  cr_assert_str_eq(out, s->data);
  close(fds[0]);
  string_free(s);
}

Test(io_push_string, write_empty_t_string) {
  int fds[2];
  t_string* s = string_new();
  char out[1];

  cr_assert_not_null(s);
  cr_assert_eq(pipe(fds), 0);
  ssize_t wrote;
  fprintf(stderr, "[DEBUG] write_empty_t_string: about to write, size=%zu\n",
          s->size);
  fflush(stderr);
  wrote = io_push_string(fds[1], s);
  fprintf(stderr, "[DEBUG] write_empty_t_string: wrote returned %zd\n", wrote);
  fflush(stderr);
  cr_assert_eq(wrote, (ssize_t)s->size);
  close(fds[1]);
  ssize_t r = read_from_fd(fds[0], out, 0);
  cr_assert_eq(r, 0);
  close(fds[0]);
  string_free(s);
}

Test(io_push_string, write_string_with_embedded_nulls) {
  int fds[2];
  t_string* s = string_new();
  char buf[6] = {'a', '\0', 'b', 'c', '\0', 'd'};
  /* initial string is empty, append later after debug*/
  char out[6] = {0};

  cr_assert_not_null(s);
  cr_assert_eq(pipe(fds), 0);
  ssize_t wrote;
  fprintf(stderr,
          "[DEBUG] write_string_with_embedded_nulls: before append, size=%zu\n",
          s->size);
  fflush(stderr);
  string_append(s, buf);
  fprintf(stderr,
          "[DEBUG] write_string_with_embedded_nulls: after append, size=%zu\n",
          s->size);
  fflush(stderr);
  fprintf(
      stderr,
      "[DEBUG] write_string_with_embedded_nulls: about to write, size=%zu\n",
      s->size);
  fflush(stderr);
  wrote = io_push_string(fds[1], s);
  fprintf(stderr,
          "[DEBUG] write_string_with_embedded_nulls: wrote returned %zd\n",
          wrote);
  fflush(stderr);
  cr_assert_eq(wrote, (ssize_t)s->size);
  close(fds[1]);
  ssize_t r = read_from_fd(fds[0], out, s->size);
  cr_assert_eq(r, (ssize_t)s->size);
  for (size_t i = 0; i < s->size; ++i) cr_assert_eq(out[i], s->data[i]);
  close(fds[0]);
  string_free(s);
}
