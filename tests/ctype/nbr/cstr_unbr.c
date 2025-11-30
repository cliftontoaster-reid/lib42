/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstr_unbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github-lfiorell <lfiorell@student.42nice.fr>        +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 21:43:00 by lfiorell            #+#    #+# */
/*   Updated: 2025/11/30 21:43:00 by lfiorell           ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <limits.h>
#include <stdlib.h>

#include "42/ctype/nbr.h"

Test(cstr_unbr, basic_and_limits) {
  char* s = cstr_unbr(0u);
  cr_assert_not_null(s);
  cr_assert_str_eq(s, "0");
  free(s);

  s = cstr_unbr(UINT_MAX);
  cr_assert_not_null(s);
  cr_assert_str_eq(s, "4294967295");
  free(s);
}

Test(cstr_unbr, roundtrip) {
  unsigned int vals[] = {0u, 1u, UINT_MAX};
  for (size_t i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
    char* s = cstr_unbr(vals[i]);
    cr_assert_not_null(s);
    unsigned int parsed = 0;
    cr_assert(cstounbr(s, &parsed));
    cr_assert_eq(parsed, vals[i]);
    free(s);
  }
}
