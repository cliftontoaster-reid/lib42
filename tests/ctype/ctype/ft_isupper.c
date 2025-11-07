/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isupper.c                                       :+:      :+:    :+:   */
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

Test(ft_isupper, basics) {
  cr_assert(ft_isupper('A'));
  cr_assert(ft_isupper('Z'));
  cr_assert_not(ft_isupper('a'));
  cr_assert_not(ft_isupper('9'));
}

Test(ft_isupper, libc_comparison_range) {
  for (int i = 0; i < 128; ++i) {
    cr_assert_eq(ft_isupper((char)i), !!isupper(i), "mismatch at %d", i);
  }
}
