/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstr_i32.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:04:49 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 16:04:57 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/ctype/nbr.h"
#include "42/memory/cstr.h"

char* cstr_i32(int32_t n) {
  uint32_t abs;
  bool neg;

  if (n < 0) {
    abs = (uint32_t)(-n);
    neg = true;
  } else {
    abs = (uint32_t)n;
    neg = false;
  }

  static char buffer[12];
  int index = 11;
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
