/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstr_u32.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:07:27 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 16:07:33 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/ctype/nbr.h"
#include "42/memory/cstr.h"

char* cstr_u32(uint32_t n) {
  static char buffer[11];
  int index = 10;
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
