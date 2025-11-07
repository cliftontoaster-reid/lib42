/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
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

Test(ft_isalpha, single_letters) {
  cr_assert(ft_isalpha('A'));
  cr_assert(ft_isalpha('Z'));
  cr_assert(ft_isalpha('a'));
  cr_assert(ft_isalpha('z'));
}

Test(ft_isalpha, non_letters) {
  cr_assert_not(ft_isalpha('0'));
  cr_assert_not(ft_isalpha('-'));
  cr_assert_not(ft_isalpha('\n'));
  cr_assert_not(ft_isalpha((char)127));
}

Test(ft_isalpha, libc_comparison_range) {
  for (int i = 0; i < 128; ++i) {
    cr_assert_eq(ft_isalpha((char)i), !!isalpha(i), "mismatch at %d", i);
  }
}
