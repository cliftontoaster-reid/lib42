/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 14:16:42 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>

#include "42/ctype/ctype.h"

Test(ft_isascii, basics) {
  cr_assert(ft_isascii((char)0));
  cr_assert(ft_isascii((char)127));
  cr_assert_not(ft_isascii((char)128));
  cr_assert_not(ft_isascii((char)-1));
}

Test(ft_isascii, explicit_range_check) {
  for (int i = -128; i <= 255; ++i) {
    unsigned char uc = (unsigned char)i;
    char c = (char)uc;
    bool expect = (i >= 0 && i <= 127);
    cr_assert_eq(ft_isascii(c), expect, "mismatch at %d (as unsigned %u)", i,
                 uc);
  }
}
