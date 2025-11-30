/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstou32.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github-lfiorell <lfiorell@student.42nice.fr>        +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:58:00 by lfiorell            #+#    #+# */
/*   Updated: 2025/11/30 20:58:00 by lfiorell           ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <limits.h>
#include <stdint.h>

#include "42/ctype/nbr.h"

Test(cstou32, basic_and_limits) {
  uint32_t out = 0;
  cr_assert(cstou32("0", &out));
  cr_assert_eq(out, 0u);
  cr_assert(cstou32("4294967295", &out));
  cr_assert_eq(out, UINT32_MAX);
}

Test(cstou32, overflow_invalid) {
  uint32_t out = 0;
  cr_assert_not(cstou32("4294967296", &out));
  cr_assert_not(cstou32("-1", &out));
  cr_assert_not(cstou32("abc", &out));
}

Test(cstou32, null_out) {
  uint32_t val = 0;
  cr_assert_not(cstou32(NULL, &val));
  cr_assert_not(cstou32("42", NULL));
}

Test(cstou32, leading_zeros_and_trailing) {
  uint32_t out = 0;
  cr_assert(cstou32("000123", &out));
  cr_assert_eq(out, 123u);
  out = 3u;
  cr_assert_not(cstou32("123abc", &out));
  cr_assert_eq(out, 3u);
}

Test(cstou32, out_preserved_on_failure) {
  uint32_t out = 1111u;
  cr_assert_not(cstou32("999999999999999999999999", &out));
  cr_assert_eq(out, 1111u);
}
