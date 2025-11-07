/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
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

Test(ft_toupper, basic_conversion) {
  cr_assert_eq(ft_toupper('a'), 'A');
  cr_assert_eq(ft_toupper('z'), 'Z');
  cr_assert_eq(ft_toupper('A'), 'A');
  cr_assert_eq(ft_toupper('0'), '0');
}

Test(ft_toupper, libc_comparison_range) {
  for (int i = 0; i < 128; ++i) {
    char c = (char)i;
    char expect = (char)toupper(i);
    cr_assert_eq(ft_toupper(c), expect, "mismatch at %d", i);
  }
}
