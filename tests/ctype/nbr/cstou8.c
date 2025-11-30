/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstou8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github-lfiorell <lfiorell@student.42nice.fr>        +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:45:00 by lfiorell            #+#    #+# */
/*   Updated: 2025/11/30 20:45:00 by lfiorell           ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <limits.h>
#include <stdint.h>

#include "42/ctype/nbr.h"

Test(cstou8, basic_values) {
  uint8_t out = 0;
  cr_assert(cstou8("0", &out));
  cr_assert_eq(out, 0);
  cr_assert(cstou8("255", &out));
  cr_assert_eq(out, 255);
}

Test(cstou8, overflow_and_invalid) {
  uint8_t out = 0;
  cr_assert_not(cstou8("256", &out));
  cr_assert_not(cstou8("-1", &out));
  cr_assert_not(cstou8("abc", &out));
}

Test(cstou8, null_and_out_null) {
  uint8_t out = 42;
  cr_assert_not(cstou8(NULL, &out));
  cr_assert_not(cstou8("123", NULL));
}

Test(cstou8, leading_zeros_and_trailing_chars) {
  uint8_t out = 0;
  cr_assert(cstou8("00042", &out));
  cr_assert_eq(out, 42);
  out = 7;
  cr_assert_not(cstou8("42abc", &out));
  cr_assert_eq(out, 7);
}

Test(cstou8, out_preserved_on_failure) {
  uint8_t out = 77;
  cr_assert_not(cstou8("9999", &out));
  cr_assert_eq(out, 77);
}
