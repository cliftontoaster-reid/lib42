/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstou64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github-lfiorell <lfiorell@student.42nice.fr>        +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 21:06:00 by lfiorell            #+#    #+# */
/*   Updated: 2025/11/30 21:06:00 by lfiorell           ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <limits.h>
#include <stdint.h>

#include "42/ctype/nbr.h"

Test(cstou64, basic_and_limits) {
  uint64_t out = 0;
  cr_assert(cstou64("0", &out));
  cr_assert_eq(out, 0ull);
  cr_assert(cstou64("18446744073709551615", &out));
  cr_assert_eq(out, UINT64_MAX);
}

Test(cstou64, overflow_and_invalid) {
  uint64_t out = 0;
  cr_assert_not(cstou64("18446744073709551616", &out));
  cr_assert_not(cstou64("-1", &out));
  cr_assert_not(cstou64("abc", &out));
}

Test(cstou64, null_checks) {
  uint64_t dummy = 0;
  cr_assert_not(cstou64(NULL, &dummy));
  cr_assert_not(cstou64("1", NULL));
}

Test(cstou64, leading_zeros_trailing) {
  uint64_t out = 0;
  cr_assert(cstou64("00000123", &out));
  cr_assert_eq(out, 123ull);
  out = 5ull;
  cr_assert_not(cstou64("123abc", &out));
  cr_assert_eq(out, 5ull);
}

Test(cstou64, out_preserved_on_failure) {
  uint64_t out = 0xCAFEBABEULL;
  cr_assert_not(cstou64("9999999999999999999999999999999", &out));
  cr_assert_eq(out, 0xCAFEBABEULL);
}
