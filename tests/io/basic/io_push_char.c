/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_push_char.c                                     :+:      :+:    :+:   */
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

Test(io_push_char, write_single_char, .init = cr_redirect_stdout) {
  ssize_t written = io_push_nchar(STDOUT_FILENO, 'A', 1);
  fflush(stdout);
  cr_assert_eq(written, 1);
  cr_assert_stdout_eq_str("A");
}

Test(io_push_char, write_null_char, .init = cr_redirect_stdout) {
  ssize_t written = io_push_nchar(STDOUT_FILENO, '\0', 1);
  fflush(stdout);
  cr_assert_eq(written, 1);
  FILE* f = cr_get_redirected_stdout();
  char c;
  cr_assert_eq(fread(&c, 1, 1, f), 1);
  cr_assert_eq(c, '\0');
}

Test(io_push_char, invalid_fd_returns_negative) {
  ssize_t written = io_push_nchar(-1, 'X', 1);
  cr_assert_eq(written, -1);
}
