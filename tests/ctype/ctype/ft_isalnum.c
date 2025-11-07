/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
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

Test(ft_isalnum, basics) {
  cr_assert(ft_isalnum('A'));
  cr_assert(ft_isalnum('z'));
  cr_assert(ft_isalnum('0'));
  cr_assert_not(ft_isalnum('!'));
  cr_assert_not(ft_isalnum(' '));
}

Test(ft_isalnum, libc_comparison_range) {
  for (int i = 0; i < 128; ++i) {
    cr_assert_eq(ft_isalnum((char)i), !!isalnum(i), "mismatch at %d", i);
  }
}
