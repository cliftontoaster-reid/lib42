/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstoi16.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github-lfiorell <lfiorell@student.42nice.fr>        +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:50:00 by lfiorell            #+#    #+# */
/*   Updated: 2025/11/30 20:50:00 by lfiorell           ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <limits.h>
#include <stdint.h>

#include "42/ctype/nbr.h"

Test(cstoi16, basic_and_limits) {
  int16_t out = 0;
  cr_assert(cstoi16("0", &out));
  cr_assert_eq(out, 0);
  cr_assert(cstoi16("32767", &out));
  cr_assert_eq(out, INT16_MAX);
  cr_assert(cstoi16("-32768", &out));
  cr_assert_eq(out, INT16_MIN);
}

Test(cstoi16, overflow_cases) {
  int16_t out = 0;
  cr_assert_not(cstoi16("32768", &out));
  cr_assert_not(cstoi16("-32769", &out));
}

Test(cstoi16, invalid_inputs_and_null) {
  int16_t out = 5;
  cr_assert_not(cstoi16("", &out));
  cr_assert_not(cstoi16("abc", &out));
  cr_assert_not(cstoi16(NULL, &out));
  cr_assert_not(cstoi16("123", NULL));
}

Test(cstoi16, leading_zeros_and_trailing_chars) {
  int16_t out = 0;
  cr_assert(cstoi16("000123", &out));
  cr_assert_eq(out, 123);
  out = 42;
  cr_assert_not(cstoi16("123abc", &out));
  cr_assert_eq(out, 42);
}

Test(cstoi16, multiple_signs_and_whitespace) {
  int16_t out = 0;
  cr_assert_not(cstoi16("+-123", &out));
  cr_assert(cstoi16("   -123", &out));
  cr_assert_eq(out, -123);
}

Test(cstoi16, long_numeric_input_safety) {
  /* build a long numeric string which should be rejected and not crash */
  char s[1026];
  for (int i = 0; i < 1024; ++i) s[i] = '9';
  s[1024] = '\0';
  int16_t out = 0x7F;
  cr_assert_not(cstoi16(s, &out));
  cr_assert_eq(out, 0x7F);
}

Test(cstoi16, embedded_nul_and_unicode_rejected) {
  int16_t out = -1;
  char s[6] = {'1', '2', '3', '\0', '4'};
  cr_assert(cstoi16(s, &out));
  cr_assert_eq(out, 123);

  /* Non-ASCII digit should be rejected */
  cr_assert_not(cstoi16("\xE2\x91\xA0", &out));
}
