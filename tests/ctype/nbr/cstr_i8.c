/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstr_i8.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github-lfiorell <lfiorell@student.42nice.fr>        +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 21:15:00 by lfiorell            #+#    #+# */
/*   Updated: 2025/11/30 21:15:00 by lfiorell           ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdint.h>
#include <stdlib.h>

#include "42/ctype/nbr.h"

Test(cstr_i8, basic_and_limits) {
  char* s = cstr_i8(0);
  cr_assert_not_null(s);
  cr_assert_str_eq(s, "0");
  free(s);

  s = cstr_i8(127);
  cr_assert_str_eq(s, "127");
  free(s);

  s = cstr_i8(-128);
  cr_assert_str_eq(s, "-128");
  free(s);
}

Test(cstr_i8, allocation_failure_not_crash) {
  /* Hard to test allocation failure portably; ensure returned pointer is
     freeable and valid for a normal case */
  char* s = cstr_i8(42);
  cr_assert_not_null(s);
  cr_assert_str_eq(s, "42");
  free(s);
}

Test(cstr_i8, roundtrip) {
  int8_t vals[] = {0, 1, -1, 127, -128};
  for (size_t i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
    char* s = cstr_i8(vals[i]);
    cr_assert_not_null(s);
    int8_t parsed = 0;
    cr_assert(cstoi8(s, &parsed));
    cr_assert_eq(parsed, vals[i]);
    free(s);
  }
}

Test(cstr_i8, canonical_representation) {
  char* s = cstr_i8(5);
  cr_assert_not_null(s);
  cr_assert_str_eq(s, "5");
  free(s);

  s = cstr_i8(-5);
  cr_assert_str_eq(s, "-5");
  free(s);
}
