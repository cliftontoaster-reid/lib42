/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstr_unbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:08:40 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 16:09:16 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctype/nbr.h"
#include "memory/cstr.h"

char* cstr_unbr(unsigned int n) {
  // int is implmententation-defined, so we use 22 to be safe
  static char buffer[22];
  int index = 21;
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
