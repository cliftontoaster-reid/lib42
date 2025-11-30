/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstr_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github-lfiorell <lfiorell@student.42nice.fr>        +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 21:40:00 by lfiorell            #+#    #+# */
/*   Updated: 2025/11/30 21:40:00 by lfiorell           ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <limits.h>
#include <stdlib.h>

#include "42/ctype/nbr.h"

Test(cstr_nbr, basic_and_limits) {
  char* s = cstr_nbr(0);
  cr_assert_not_null(s);
  cr_assert_str_eq(s, "0");
  free(s);

  s = cstr_nbr(INT_MAX);
  cr_assert_not_null(s);
  /* The exact decimal is platform-specific when sizeof(int) may vary;
     but on typical platforms it's 2147483647 */
  cr_assert_str_eq(s, "2147483647");
  free(s);

  s = cstr_nbr(INT_MIN);
  cr_assert_str_eq(s, "-2147483648");
  free(s);
}

Test(cstr_nbr, roundtrip) {
  int values[] = {0, 1, -1, INT_MAX, INT_MIN};
  for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); ++i) {
    char* s = cstr_nbr(values[i]);
    cr_assert_not_null(s);
    int parsed = 0;
    cr_assert(cstonbr(s, &parsed));
    cr_assert_eq(parsed, values[i]);
    free(s);
  }
}
