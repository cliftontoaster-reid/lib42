/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstounbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github-lfiorell <lfiorell@student.42nice.fr>        +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 21:12:00 by lfiorell            #+#    #+# */
/*   Updated: 2025/11/30 21:12:00 by lfiorell           ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <limits.h>
#include <stdlib.h>

#include "42/ctype/nbr.h"

Test(cstounbr, basic_and_limits) {
  unsigned int out = 0;
  cr_assert(cstounbr("0", &out));
  cr_assert_eq(out, 0u);
  cr_assert(cstounbr("4294967295", &out));
  cr_assert_eq(out, UINT_MAX);
}

Test(cstounbr, overflow_invalid) {
  unsigned int out = 0;
  cr_assert_not(cstounbr("4294967296", &out));
  cr_assert_not(cstounbr("-1", &out));
  cr_assert_not(cstounbr("abc", &out));
}

Test(cstounbr, null_checks) {
  unsigned int out = 0;
  cr_assert_not(cstounbr(NULL, &out));
  cr_assert_not(cstounbr("1", NULL));
}

Test(cstounbr, leading_zeros_trailing) {
  unsigned int out = 0u;
  cr_assert(cstounbr("00000123", &out));
  cr_assert_eq(out, 123u);
  out = 1u;
  cr_assert_not(cstounbr("123abc", &out));
  cr_assert_eq(out, 1u);
}

Test(cstounbr, out_preserved_when_failure) {
  unsigned int out = 12345u;
  cr_assert_not(cstounbr("99999999999999999999", &out));
  cr_assert_eq(out, 12345u);
}
