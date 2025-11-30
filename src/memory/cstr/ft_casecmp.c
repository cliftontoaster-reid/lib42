/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_casecmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:15:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/30 20:22:27 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/ctype/ctype.h"
#include "42/memory/cstr.h"

int ft_casecmp(const char* s1, const char* s2) {
  size_t i = 0;
  while (s1[i] && s2[i]) {
    int a = (unsigned char)ft_tolower(s1[i]);
    int b = (unsigned char)ft_tolower(s2[i]);
    if (a != b) {
      return (unsigned char)a - (unsigned char)b;
    }
    i++;
  }
  {
    int a = (unsigned char)ft_tolower(s1[i]);
    int b = (unsigned char)ft_tolower(s2[i]);
    return (unsigned char)a - (unsigned char)b;
  }
}
