/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstr_u8.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github-lfiorell <lfiorell@student.42nice.fr>        +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 21:18:00 by lfiorell            #+#    #+# */
/*   Updated: 2025/11/30 21:18:00 by lfiorell           ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdint.h>
#include <stdlib.h>

#include "42/ctype/nbr.h"

Test(cstr_u8, basic) {
  char* s = cstr_u8(0);
  cr_assert_not_null(s);
  cr_assert_str_eq(s, "0");
  free(s);

  s = cstr_u8(255);
  cr_assert_str_eq(s, "255");
  free(s);
}

Test(cstr_u8, roundtrip) {
  uint8_t vals[] = {0, 1, 255};
  for (size_t i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
    char* s = cstr_u8(vals[i]);
    cr_assert_not_null(s);
    uint8_t parsed = 0;
    cr_assert(cstou8(s, &parsed));
    cr_assert_eq(parsed, vals[i]);
    free(s);
  }
}
