/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstou16.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github-lfiorell <lfiorell@student.42nice.fr>        +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:52:00 by lfiorell            #+#    #+# */
/*   Updated: 2025/11/30 20:52:00 by lfiorell           ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <limits.h>
#include <stdint.h>

#include "42/ctype/nbr.h"

Test(cstou16, basic_and_limits) {
  uint16_t out = 0;
  cr_assert(cstou16("0", &out));
  cr_assert_eq(out, 0);
  cr_assert(cstou16("65535", &out));
  cr_assert_eq(out, UINT16_MAX);
}

Test(cstou16, overflow_and_invalid) {
  uint16_t out = 0;
  cr_assert_not(cstou16("65536", &out));
  cr_assert_not(cstou16("-1", &out));
  cr_assert_not(cstou16("abc", &out));
}

Test(cstou16, out_preserved_on_failure) {
  uint16_t out = 1234;
  cr_assert_not(cstou16("9999999999", &out));
  cr_assert_eq(out, 1234);
}

Test(cstou16, null_and_out_null) {
  uint16_t out = 0;
  cr_assert_not(cstou16(NULL, &out));
  cr_assert_not(cstou16("123", NULL));
}
