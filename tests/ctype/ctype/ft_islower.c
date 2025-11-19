/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_islower.c                                       :+:      :+:    :+:   */
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

Test(ft_islower, basics) {
  cr_assert(ft_islower('a'));
  cr_assert(ft_islower('m'));
  cr_assert_not(ft_islower('A'));
  cr_assert_not(ft_islower('0'));
}

Test(ft_islower, libc_comparison_range) {
  for (int i = 0; i < 128; ++i) {
    cr_assert_eq(ft_islower((char)i), !!islower(i), "mismatch at %d", i);
  }
}
