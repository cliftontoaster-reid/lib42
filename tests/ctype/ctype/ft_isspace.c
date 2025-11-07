/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
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

Test(ft_isspace, known_spaces) {
  cr_assert(ft_isspace(' '));
  cr_assert(ft_isspace('\t'));
  cr_assert(ft_isspace('\n'));
  cr_assert(ft_isspace('\r'));
  cr_assert(ft_isspace('\v'));
  cr_assert(ft_isspace('\f'));
}

Test(ft_isspace, non_space_chars) {
  cr_assert_not(ft_isspace('A'));
  cr_assert_not(ft_isspace('0'));
  cr_assert_not(ft_isspace('!'));
}

Test(ft_isspace, libc_comparison_range) {
  for (int i = 0; i < 128; ++i) {
    cr_assert_eq(ft_isspace((char)i), !!isspace(i), "mismatch at %d", i);
  }
}
