/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstr_i32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github-lfiorell <lfiorell@student.42nice.fr>        +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 21:27:00 by lfiorell            #+#    #+# */
/*   Updated: 2025/11/30 21:27:00 by lfiorell           ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>

#include "42/ctype/nbr.h"

Test(cstr_i32, basic_and_limits) {
  char* s = cstr_i32(0);
  cr_assert_not_null(s);
  cr_assert_str_eq(s, "0");
  free(s);

  s = cstr_i32(INT32_MAX);
  cr_assert_str_eq(s, "2147483647");
  free(s);

  s = cstr_i32(INT32_MIN);
  cr_assert_str_eq(s, "-2147483648");
  free(s);
}

Test(cstr_i32, roundtrip) {
  int32_t values[] = {0, 1, -1, INT32_MAX, INT32_MIN};
  for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); ++i) {
    char* s = cstr_i32(values[i]);
    cr_assert_not_null(s);
    int32_t parsed = 0;
    cr_assert(cstoi32(s, &parsed));
    cr_assert_eq(parsed, values[i]);
    free(s);
  }
}
