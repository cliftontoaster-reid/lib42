/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
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

Test(ft_isdigit, basics) {
  cr_assert(ft_isdigit('0'));
  cr_assert(ft_isdigit('5'));
  cr_assert(ft_isdigit('9'));
  cr_assert_not(ft_isdigit('a'));
  cr_assert_not(ft_isdigit(' '));
}

Test(ft_isdigit, libc_comparison_range) {
  for (int i = 0; i < 128; ++i) {
    cr_assert_eq(ft_isdigit((char)i), !!isdigit(i), "mismatch at %d", i);
  }
}
