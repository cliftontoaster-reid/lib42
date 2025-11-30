/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstoi32.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github-lfiorell <lfiorell@student.42nice.fr>        +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:55:00 by lfiorell            #+#    #+# */
/*   Updated: 2025/11/30 20:55:00 by lfiorell           ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <limits.h>
#include <stdint.h>

#include "42/ctype/nbr.h"

Test(cstoi32, basic_and_limits) {
  int32_t out = 0;
  cr_assert(cstoi32("0", &out));
  cr_assert_eq(out, 0);
  cr_assert(cstoi32("2147483647", &out));
  cr_assert_eq(out, INT32_MAX);
  cr_assert(cstoi32("-2147483648", &out));
  cr_assert_eq(out, INT32_MIN);
}

Test(cstoi32, overflow_cases) {
  int32_t out = 0;
  cr_assert_not(cstoi32("2147483648", &out));
  cr_assert_not(cstoi32("-2147483649", &out));
}

Test(cstoi32, invalid_and_null) {
  int32_t out = 1;
  cr_assert_not(cstoi32("", &out));
  cr_assert_not(cstoi32("alpha", &out));
  cr_assert_not(cstoi32(NULL, &out));
  cr_assert_not(cstoi32("123", NULL));
}

Test(cstoi32, trailing_and_signs) {
  int32_t out = 0;
  cr_assert_not(cstoi32("123abc", &out));
  cr_assert_not(cstoi32("+-123", &out));
  cr_assert(cstoi32("  -123", &out));
  cr_assert_eq(out, -123);
}

Test(cstoi32, out_preserved_when_failure) {
  int32_t out = 9999;
  cr_assert_not(cstoi32("2147483648", &out));
  cr_assert_eq(out, 9999);
}
