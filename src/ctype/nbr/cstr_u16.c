/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstr_u16.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:07:03 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 16:07:08 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctype/nbr.h"
#include "memory/cstr.h"

char* cstr_u16(uint16_t n) {
  static char buffer[6];
  int index = 5;
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
