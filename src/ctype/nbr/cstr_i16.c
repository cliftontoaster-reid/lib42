/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstr_i16.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:01:24 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 16:04:36 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctype/nbr.h"
#include "memory/cstr.h"

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

  static char buffer[6];
  int index = 5;
  buffer[index--] = '\0';
  while (abs > 0) {
    buffer[index--] = (char)((abs % 10) + '0');
    abs /= 10;
  }
  if (neg) {
    buffer[index--] = '-';
  }
  return ft_strdup(&buffer[index + 1]);
}
