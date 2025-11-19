/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 14:16:42 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <ctype.h>

#include "42/ctype/ctype.h"

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
