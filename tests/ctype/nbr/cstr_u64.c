/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstr_u64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github-lfiorell <lfiorell@student.42nice.fr>        +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 21:37:00 by lfiorell            #+#    #+# */
/*   Updated: 2025/11/30 21:37:00 by lfiorell           ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>

#include "42/ctype/nbr.h"

Test(cstr_u64, basic_and_limits) {
  char* s = cstr_u64(0ull);
  cr_assert_not_null(s);
  cr_assert_str_eq(s, "0");
  free(s);

  s = cstr_u64(UINT64_MAX);
  cr_assert_str_eq(s, "18446744073709551615");
  free(s);
}

Test(cstr_u64, roundtrip) {
  uint64_t values[] = {0ull, 1ull, 123456789012345ull, UINT64_MAX};
  for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); ++i) {
    char* s = cstr_u64(values[i]);
    cr_assert_not_null(s);
    uint64_t parsed = 0;
    cr_assert(cstou64(s, &parsed));
    cr_assert_eq(parsed, values[i]);
    free(s);
  }
}
