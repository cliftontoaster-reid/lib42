/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_push_ldouble.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:00:00 by lfiorell           #+#    #+# */
/*   Updated: 2025/11/29 20:20:03 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

#include "42/io/basic.h"

Test(io_push_ldouble, write_zero_precision_3, .init = cr_redirect_stdout) {
  ssize_t wrote = io_push_ldouble(STDOUT_FILENO, 0.0L, 3);
  fflush(stdout);
  cr_assert_eq(wrote, 5);
  cr_assert_stdout_eq_str("0.000");
}

Test(io_push_ldouble, write_positive, .init = cr_redirect_stdout) {
  ssize_t wrote = io_push_ldouble(STDOUT_FILENO, 1.234567890123456789L, 9);
  fflush(stdout);
  cr_assert_gt(wrote, 0);
  FILE* f = cr_get_redirected_stdout();
  char out[32] = {0};
  fread(out, 1, 31, f);
  cr_assert(strncmp(out, "1.234567890", 11) == 0 ||
            strncmp(out, "1.234567891", 11) == 0);
}

Test(io_push_ldouble, write_nan, .init = cr_redirect_stdout) {
  ssize_t wrote = io_push_ldouble(STDOUT_FILENO, NAN, 3);
  fflush(stdout);
  cr_assert_eq(wrote, 3);
  cr_assert_stdout_eq_str("nan");
}

Test(io_push_ldouble, write_inf, .init = cr_redirect_stdout) {
  ssize_t wrote = io_push_ldouble(STDOUT_FILENO, INFINITY, 2);
  fflush(stdout);
  cr_assert_eq(wrote, 3);
  cr_assert_stdout_eq_str("inf");
}

Test(io_push_ldouble, write_minus_inf, .init = cr_redirect_stdout) {
  ssize_t wrote = io_push_ldouble(STDOUT_FILENO, -INFINITY, 2);
  fflush(stdout);
  cr_assert_eq(wrote, 4);
  cr_assert_stdout_eq_str("-inf");
}
