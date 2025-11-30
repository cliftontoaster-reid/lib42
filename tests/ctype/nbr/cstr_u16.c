/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstr_u16.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github-lfiorell <lfiorell@student.42nice.fr>        +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 21:24:00 by lfiorell            #+#    #+# */
/*   Updated: 2025/11/30 21:24:00 by lfiorell           ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>

#include "42/ctype/nbr.h"

Test(cstr_u16, basic_and_limits) {
  char* s = cstr_u16(0);
  cr_assert_not_null(s);
  cr_assert_str_eq(s, "0");
  free(s);

  s = cstr_u16(65535);
  cr_assert_str_eq(s, "65535");
  free(s);
}

Test(cstr_u16, roundtrip) {
  uint16_t vals[] = {0u, 1u, 65535u};
  for (size_t i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
    char* s = cstr_u16(vals[i]);
    cr_assert_not_null(s);
    uint16_t parsed = 0;
    cr_assert(cstou16(s, &parsed));
    cr_assert_eq(parsed, vals[i]);
    free(s);
  }
}
