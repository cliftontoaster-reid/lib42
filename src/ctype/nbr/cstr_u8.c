/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstr_u8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:06:42 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 16:06:48 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/ctype/nbr.h"
#include "42/memory/cstr.h"

char* cstr_u8(uint8_t n) {
  static char buffer[4];
  int index = 3;
  buffer[index--] = '\0';
  if (n == 0) {
    buffer[index--] = '0';
  } else {
    while (n > 0) {
      buffer[index--] = (char)((n % 10) + '0');
      n /= 10;
    }
  }
  return ft_strdup(&buffer[index + 1]);
}
