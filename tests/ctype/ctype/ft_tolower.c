/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@invalid>                   +#+  +:+       +#+ */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:00:00 by copilot           #+#    #+#             */
/*   Updated: 2025/11/07 10:00:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <ctype.h>

#include "ctype/ctype.h"

Test(ft_tolower, basic_conversion) {
  cr_assert_eq(ft_tolower('A'), 'a');
  cr_assert_eq(ft_tolower('Z'), 'z');
  cr_assert_eq(ft_tolower('a'), 'a');
  cr_assert_eq(ft_tolower('0'), '0');
}

Test(ft_tolower, libc_comparison_range) {
  for (int i = 0; i < 128; ++i) {
    char c = (char)i;
    char expect = (char)tolower(i);
    cr_assert_eq(ft_tolower(c), expect, "mismatch at %d", i);
  }
}
