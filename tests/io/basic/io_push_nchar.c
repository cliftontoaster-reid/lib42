/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_push_nchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:00:00 by lfiorell           #+#    #+# */
/*   Updated: 2025/11/29 20:20:03 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <string.h>
#include <unistd.h>

#include "42/io/basic.h"

Test(io_push_nchar, write_5_times, .init = cr_redirect_stdout) {
  ssize_t wrote = io_push_nchar(STDOUT_FILENO, 'B', 5);
  fflush(stdout);
  cr_assert_eq(wrote, 5);
  cr_assert_stdout_eq_str("BBBBB");
}

Test(io_push_nchar, write_zero_times, .init = cr_redirect_stdout) {
  ssize_t wrote = io_push_nchar(STDOUT_FILENO, 'C', 0);
  fflush(stdout);
  cr_assert_eq(wrote, 0);
  cr_assert_stdout_eq_str("");
}

Test(io_push_nchar, invalid_fd_returns_negative) {
  ssize_t wrote = io_push_nchar(-1, 'D', 10);
  cr_assert_eq(wrote, -1);
}

Test(io_push_nchar, write_many_chars, .init = cr_redirect_stdout) {
  const size_t N = 1024;
  char* expected = malloc(N + 1);
  cr_assert_not_null(expected);
  memset(expected, 'E', N);
  expected[N] = '\0';

  ssize_t wrote = io_push_nchar(STDOUT_FILENO, 'E', N);
  fflush(stdout);
  cr_assert_eq(wrote, N);
  cr_assert_stdout_eq_str(expected);
  free(expected);
}
