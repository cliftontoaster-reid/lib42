/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstr_i64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github-lfiorell <lfiorell@student.42nice.fr>        +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 21:34:00 by lfiorell            #+#    #+# */
/*   Updated: 2025/11/30 21:34:00 by lfiorell           ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>

#include "42/ctype/nbr.h"

Test(cstr_i64, basic_and_limits) {
  char* s = cstr_i64(0);
  cr_assert_not_null(s);
  cr_assert_str_eq(s, "0");
  free(s);

  s = cstr_i64(INT64_MAX);
  cr_assert_str_eq(s, "9223372036854775807");
  free(s);

  s = cstr_i64(INT64_MIN);
  cr_assert_str_eq(s, "-9223372036854775808");
  free(s);
}

Test(cstr_i64, zero_and_roundtrip) {
  char* s = cstr_i64(0);
  cr_assert_not_null(s);
  cr_assert_str_eq(s, "0");
  free(s);

  int64_t values[] = {0, 1, -1, INT64_MAX, INT64_MIN};
  for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); ++i) {
    char* ss = cstr_i64(values[i]);
    cr_assert_not_null(ss);
    int64_t parsed = 0;
    cr_assert(cstoi64(ss, &parsed));
    cr_assert_eq(parsed, values[i]);
    free(ss);
  }
}

Test(cstr_i64, canonical_and_alloc_freeable) {
  char* s = cstr_i64(123000);
  cr_assert_not_null(s);
  cr_assert_str_eq(s, "123000");
  free(s);
  s = cstr_i64(-9223372036854775807LL - 1);
  cr_assert_not_null(s);
  cr_assert_str_eq(s, "-9223372036854775808");
  free(s);
}
