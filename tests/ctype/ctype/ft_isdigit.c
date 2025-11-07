/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
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
