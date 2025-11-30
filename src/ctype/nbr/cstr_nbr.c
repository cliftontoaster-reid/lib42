/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstr_nbr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:05:38 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 16:09:27 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/ctype/nbr.h"
#include "42/memory/cstr.h"

char* cstr_nbr(int n) {
  bool neg = false;
  unsigned int abs;

  if (n < 0) {
    neg = true;
    abs = (unsigned int)(-n);
  } else {
    abs = (unsigned int)n;
  }

  // int is implmententation-defined, so we use 22 to be safe
  static char buffer[22];
  int index = 21;
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
