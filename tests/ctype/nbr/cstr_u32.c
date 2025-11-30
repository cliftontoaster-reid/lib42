/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstr_u32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github-lfiorell <lfiorell@student.42nice.fr>        +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 21:30:00 by lfiorell            #+#    #+# */
/*   Updated: 2025/11/30 21:30:00 by lfiorell           ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>

#include "42/ctype/nbr.h"

Test(cstr_u32, basic_and_limits) {
  char* s = cstr_u32(0u);
  cr_assert_not_null(s);
  cr_assert_str_eq(s, "0");
  free(s);

  s = cstr_u32(UINT32_MAX);
  cr_assert_str_eq(s, "4294967295");
  free(s);
}

Test(cstr_u32, roundtrip) {
  uint32_t values[] = {0u, 1u, 123456789u, UINT32_MAX};
  for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); ++i) {
    char* s = cstr_u32(values[i]);
    cr_assert_not_null(s);
    uint32_t parsed = 0;
    cr_assert(cstou32(s, &parsed));
    cr_assert_eq(parsed, values[i]);
    free(s);
  }
}
