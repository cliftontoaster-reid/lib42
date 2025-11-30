/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstoi64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github-lfiorell <lfiorell@student.42nice.fr>        +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 21:02:00 by lfiorell            #+#    #+# */
/*   Updated: 2025/11/30 21:02:00 by lfiorell           ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <limits.h>
#include <stdint.h>

#include "42/ctype/nbr.h"

Test(cstoi64, basic_and_limits) {
  int64_t out = 0;
  cr_assert(cstoi64("0", &out));
  cr_assert_eq(out, 0);
  cr_assert(cstoi64("9223372036854775807", &out));
  cr_assert_eq(out, INT64_MAX);
  cr_assert(cstoi64("-9223372036854775808", &out));
  cr_assert_eq(out, INT64_MIN);
}

Test(cstoi64, overflow_cases) {
  int64_t out = 0;
  cr_assert_not(cstoi64("9223372036854775808", &out));
  cr_assert_not(cstoi64("-9223372036854775809", &out));
}

Test(cstoi64, invalid_nulls) {
  int64_t value = 7;
  cr_assert_not(cstoi64(NULL, &value));
  cr_assert_not(cstoi64("text", &value));
  cr_assert_not(cstoi64("123", NULL));
}

Test(cstoi64, trailing_signs_and_whitespace) {
  int64_t out = 0;
  cr_assert_not(cstoi64("123abc", &out));
  cr_assert_not(cstoi64("+-123", &out));
  cr_assert(cstoi64("\t+123\n", &out));
  cr_assert_eq(out, 123);
}

Test(cstoi64, out_preserved_when_failure) {
  int64_t out = 0xABCDEF;
  cr_assert_not(cstoi64("9223372036854775808", &out));
  cr_assert_eq(out, (int64_t)0xABCDEF);
}
