/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_casecmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:15:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/29 16:40:26 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/memory/cstr.h"
#include "42/ctype/ctype.h"

int ft_casecmp(const char* s1, const char* s2) {
  size_t i = 0;
  while (s1[i] && s2[i]) {
    unsigned char c1 = (unsigned char)s1[i];
    unsigned char c2 = (unsigned char)s2[i];
    if (ft_tolower(c1) != ft_tolower(c2)) {
      return ft_tolower(c1) - ft_tolower(c2);
    }
    i++;
  }
  return ft_tolower((unsigned char)s1[i]) - ft_tolower((unsigned char)s2[i]);
}
