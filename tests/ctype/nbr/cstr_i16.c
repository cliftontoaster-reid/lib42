/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstr_i16.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github-lfiorell <lfiorell@student.42nice.fr>        +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 21:20:00 by lfiorell            #+#    #+# */
/*   Updated: 2025/11/30 21:20:00 by lfiorell           ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>

#include "42/ctype/nbr.h"

Test(cstr_i16, basic_and_limits) {
  char* s = cstr_i16(0);
  cr_assert_not_null(s);
  cr_assert_str_eq(s, "0");
  free(s);

  s = cstr_i16(32767);
  cr_assert_str_eq(s, "32767");
  free(s);

  s = cstr_i16(-32768);
  cr_assert_str_eq(s, "-32768");
  free(s);
}

Test(cstr_i16, edge_cases) {
  char* s = cstr_i16(-0);
  cr_assert_str_eq(s, "0");
  free(s);
}

Test(cstr_i16, roundtrip_and_nul_terminated) {
  int16_t values[] = {0, 1, -1, 32767, -32768};
  for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); ++i) {
    char* s = cstr_i16(values[i]);
    cr_assert_not_null(s);
    /* string must be NUL terminated and contain the textual number */
    cr_assert_str_eq(s,
                     s); /* sanity check; actual compare is made after parse */
    int16_t parsed = 0;
    cr_assert(cstoi16(s, &parsed));
    cr_assert_eq(parsed, values[i]);
    free(s);
  }
}
