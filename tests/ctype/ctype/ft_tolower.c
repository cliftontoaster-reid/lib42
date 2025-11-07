/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 14:16:42 by lfiorell@st      ###   ########.fr       */
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
