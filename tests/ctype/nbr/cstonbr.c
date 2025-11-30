/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstonbr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github-lfiorell <lfiorell@student.42nice.fr>        +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 21:10:00 by lfiorell            #+#    #+# */
/*   Updated: 2025/11/30 21:10:00 by lfiorell           ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <limits.h>
#include <stdlib.h>

#include "42/ctype/nbr.h"

Test(cstonbr, basic_values_and_limits) {
  int out = 0;
  cr_assert(cstonbr("0", &out));
  cr_assert_eq(out, 0);
  cr_assert(cstonbr("2147483647", &out));
  cr_assert_eq(out, INT_MAX);
  cr_assert(cstonbr("-2147483648", &out));
  cr_assert_eq(out, INT_MIN);
}

Test(cstonbr, overflow_invalid) {
  int out = 0;
  cr_assert_not(cstonbr("2147483648", &out));
  cr_assert_not(cstonbr("-2147483649", &out));
  cr_assert_not(cstonbr("non-digit", &out));
}

Test(cstonbr, nulls) {
  int out = 0;
  cr_assert_not(cstonbr(NULL, &out));
  cr_assert_not(cstonbr("42", NULL));
}

Test(cstonbr, leading_zeros_and_trailing) {
  int out = 0;
  cr_assert(cstonbr("000007", &out));
  cr_assert_eq(out, 7);
  out = 99;
  cr_assert_not(cstonbr("123abc", &out));
  cr_assert_eq(out, 99);
}

Test(cstonbr, out_preserved_on_failure) {
  int out = -99;
  cr_assert_not(cstonbr("999999999999999", &out));
  cr_assert_eq(out, -99);
}
