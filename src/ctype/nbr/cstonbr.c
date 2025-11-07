/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstonbr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:32:27 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 15:55:01 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "ctype/ctype.h"
#include "ctype/nbr.h"

bool cstonbr(const char* str, int* out) {
  if (str == NULL || out == NULL) return false;
  unsigned int value = 0;
  bool negative = false;

  while (ft_isspace(*str)) str++;
  while (*str == '+' || *str == '-') {
    if (*str == '-') negative = !negative;
    str++;
  }
  if (!ft_isdigit(*str)) return false;

  while (ft_isdigit(*str)) {
    unsigned int digit = (unsigned int)(*str - '0');

    value = value * 10 + digit;
    if (negative && value > INT_MAX) return false;
    if (!negative && value > INT_MAX) return false;
    str++;
  }

  if (negative) {
    *out = (int)(-value);
  } else {
    *out = (int)value;
  }
  return true;
}
