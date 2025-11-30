/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_push_nbytes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:00:00 by lfiorell           #+#    #+# */
/*   Updated: 2025/11/29 20:20:03 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "42/io/basic.h"

Test(io_push_nbytes, write_n_bytes, .init = cr_redirect_stdout) {
  const char* s = "abcde";
  ssize_t wrote = io_push_nbytes(STDOUT_FILENO, s, 5);
  fflush(stdout);
  cr_assert_eq(wrote, 5);
  cr_assert_stdout_eq_str("abcde");
}

Test(io_push_nbytes, write_zero_bytes, .init = cr_redirect_stdout) {
  const char* s = "abc";
  ssize_t wrote = io_push_nbytes(STDOUT_FILENO, s, 0);
  fflush(stdout);
  cr_assert_eq(wrote, 0);
  cr_assert_stdout_eq_str("");
}

Test(io_push_nbytes, write_buffer_with_nulls, .init = cr_redirect_stdout) {
  char buf[6] = {'a', '\0', 'b', '\0', 'c', '\0'};
  ssize_t wrote = io_push_nbytes(STDOUT_FILENO, buf, 6);
  fflush(stdout);
  cr_assert_eq(wrote, 6);
  FILE* f = cr_get_redirected_stdout();
  char out[6] = {0};
  cr_assert_eq(fread(out, 1, 6, f), 6);
  for (size_t i = 0; i < 6; ++i) cr_assert_eq(out[i], buf[i]);
}

Test(io_push_nbytes, write_large_buffer, .init = cr_redirect_stdout) {
  size_t N = 4096;
  char* buf = malloc(N);
  cr_assert_not_null(buf);
  for (size_t i = 0; i < N; ++i) buf[i] = (char)('a' + (i % 26));

  ssize_t wrote = io_push_nbytes(STDOUT_FILENO, buf, N);
  fflush(stdout);
  cr_assert_eq(wrote, (ssize_t)N);

  FILE* f = cr_get_redirected_stdout();
  char* out = malloc(N);
  cr_assert_not_null(out);
  cr_assert_eq(fread(out, 1, N, f), N);
  for (size_t i = 0; i < N; ++i) cr_assert_eq(out[i], buf[i]);
  free(buf);
  free(out);
}
