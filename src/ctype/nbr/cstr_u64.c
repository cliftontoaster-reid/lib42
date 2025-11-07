/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstr_u64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:08:33 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 16:08:38 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctype/nbr.h"
#include "memory/cstr.h"

char* cstr_u64(uint64_t n) {
  static char buffer[21];
  int index = 20;
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
