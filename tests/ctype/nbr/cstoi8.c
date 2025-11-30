/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstoi8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github-lfiorell <lfiorell@student.42nice.fr>        +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:40:00 by lfiorell            #+#    #+# */
/*   Updated: 2025/11/30 20:40:00 by lfiorell           ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <limits.h>
#include <stdint.h>

#include "42/ctype/nbr.h"

Test(cstoi8, basic_positive_negative_zero) {
  int8_t out = 42;
  cr_assert(cstoi8("0", &out));
  cr_assert_eq(out, 0);
  cr_assert(cstoi8("127", &out));
  cr_assert_eq(out, 127);
  cr_assert(cstoi8("-128", &out));
  cr_assert_eq(out, -128);
}

Test(cstoi8, overflow_and_underflow) {
  int8_t out = 0;
  cr_assert_not(cstoi8("128", &out));
  cr_assert_not(cstoi8("-129", &out));
}

Test(cstoi8, invalid_strings_nulls) {
  int8_t value = 5;
  cr_assert_not(cstoi8("", &value));
  cr_assert_not(cstoi8("abc", &value));
  cr_assert_not(cstoi8(NULL, &value));
  cr_assert_not(cstoi8("123", NULL));
}

Test(cstoi8, whitespace_and_leading_signs) {
  int8_t out = 0;
  cr_assert(cstoi8("  12", &out));
  cr_assert_eq(out, 12);
  cr_assert(cstoi8("+12", &out));
  cr_assert_eq(out, 12);
  cr_assert(cstoi8("-0", &out));
  cr_assert_eq(out, 0);
}

Test(cstoi8, trailing_chars_multiple_signs_and_out_preserved) {
  int8_t out = 127;
  cr_assert_not(cstoi8("12abc", &out));
  cr_assert_eq(out, 127);
  cr_assert_not(cstoi8("+-12", &out));
  cr_assert_eq(out, 127);
}

Test(cstoi8, out_preserved_when_failure) {
  int8_t out = -42;
  cr_assert_not(cstoi8("999999999999", &out));
  cr_assert_eq(out, -42);
}
