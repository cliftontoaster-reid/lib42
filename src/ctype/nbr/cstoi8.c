/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstoi8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:23:52 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 15:55:54 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/ctype/ctype.h"
#include "42/ctype/nbr.h"

bool cstoi8(const char* str, int8_t* out) {
  uint8_t value = 0;
  bool negative = false;

  while (ft_isspace(*str)) str++;
  while (*str == '+' || *str == '-') {
    if (*str == '-') negative = !negative;
    str++;
  }
  if (!ft_isdigit(*str)) return false;

  while (ft_isdigit(*str)) {
    uint8_t digit = (uint8_t)(*str - '0');

    value = value * 10 + digit;
    if (negative && value > INT8_MAX) return false;
    if (!negative && value >= INT8_MAX) return false;
    str++;
  }

  if (negative) {
    *out = (int8_t)(-value);
  } else {
    *out = (int8_t)value;
  }
  return true;
}
