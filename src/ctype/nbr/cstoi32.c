/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstoi32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:29:16 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 15:55:24 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "42/ctype/ctype.h"
#include "42/ctype/nbr.h"

bool cstoi32(const char* str, int32_t* out) {
  if (str == NULL || out == NULL) return false;
  uint32_t value = 0;
  bool negative = false;

  while (ft_isspace(*str)) str++;
  while (*str == '+' || *str == '-') {
    if (*str == '-') negative = !negative;
    str++;
  }
  if (!ft_isdigit(*str)) return false;

  while (ft_isdigit(*str)) {
    uint32_t digit = (uint32_t)(*str - '0');

    value = value * 10 + digit;
    if (negative && value > INT32_MAX) return false;
    if (!negative && value >= INT32_MAX) return false;
    str++;
  }

  if (negative) {
    *out = (int32_t)(-value);
  } else {
    *out = (int32_t)value;
  }
  return true;
}
