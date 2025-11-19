/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstr_i8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:56:59 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 16:03:09 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/ctype/nbr.h"
#include "42/memory/cstr.h"

char* cstr_i8(int8_t n) {
  uint8_t abs;
  bool neg;

  if (n < 0) {
    abs = (uint8_t)(-n);
    neg = true;
  } else {
    abs = (uint8_t)n;
    neg = false;
  }

  static char buffer[5];
  int index = 4;
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
