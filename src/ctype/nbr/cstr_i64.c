/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstr_i64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:05:09 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/30 19:22:26 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/ctype/nbr.h"
#include "42/memory/cstr.h"

char* cstr_i64(int64_t n) {
  uint64_t abs;
  bool neg;

  if (n < 0) {
    abs = (uint64_t)(-n);
    neg = true;
  } else {
    abs = (uint64_t)n;
    neg = false;
  }

  static char buffer[21];
  int index = 20;
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
