/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstonbr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:32:27 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/30 19:22:26 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "42/ctype/ctype.h"
#include "42/ctype/nbr.h"

bool cstonbr(const char* str, int* out) {
  if (str == NULL || out == NULL) return false;
  unsigned int value = 0;
  bool negative = false;

  while (ft_isspace(*str)) str++;
  if (*str == '+' || *str == '-') {
    if (*str == '-') negative = true;
    str++;
  }
  if (!ft_isdigit(*str)) return false;

  while (ft_isdigit(*str)) {
    unsigned int digit = (unsigned int)(*str - '0');

    value = value * 10 + digit;
    if (negative && value > (unsigned int)INT_MAX + 1) return false;
    if (!negative && value > INT_MAX) return false;
    str++;
  }
  while (ft_isspace(*str)) str++;
  if (*str != '\0') return false;

  if (negative) {
    *out = (int)(-(int)value);
  } else {
    *out = (int)value;
  }
  return true;
}
