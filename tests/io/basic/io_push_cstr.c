/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_push_cstr.c                                     :+:      :+:    :+:   */
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

Test(io_push_cstr, write_regular_string, .init = cr_redirect_stdout) {
  ssize_t wrote = io_push_cstr(STDOUT_FILENO, "hello");
  fflush(stdout);
  cr_assert_eq(wrote, 5);
  cr_assert_stdout_eq_str("hello");
}

Test(io_push_cstr, write_empty_string, .init = cr_redirect_stdout) {
  ssize_t wrote = io_push_cstr(STDOUT_FILENO, "");
  fflush(stdout);
  cr_assert_eq(wrote, 0);
  cr_assert_stdout_eq_str("");
}

Test(io_push_cstr, write_string_with_special_chars,
     .init = cr_redirect_stdout) {
  const char* source = "line1\nline2\tOK";
  ssize_t wrote = io_push_cstr(STDOUT_FILENO, source);
  fflush(stdout);
  cr_assert_eq(wrote, (ssize_t)strlen(source));
  cr_assert_stdout_eq_str(source);
}
