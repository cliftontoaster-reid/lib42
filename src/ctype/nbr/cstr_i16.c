/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstr_i16.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:01:24 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/30 19:22:26 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/ctype/nbr.h"
#include "42/memory/cstr.h"

char* cstr_i16(int16_t n) {
  uint16_t abs;
  bool neg;

  if (n < 0) {
    abs = (uint16_t)(-n);
    neg = true;
  } else {
    abs = (uint16_t)n;
    neg = false;
  }

  static char buffer[7];
  int index = 6;
  buffer[index--] = '\0';
  if (abs == 0) {
    buffer[index--] = '0';
  } else {
    while (abs > 0) {
      buffer[index--] = (char)((abs % 10) + '0');
      abs /= 10;
    }
  }
  if (neg) {
    buffer[index--] = '-';
  }
  return ft_strdup(&buffer[index + 1]);
}
