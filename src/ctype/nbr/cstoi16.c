/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstoi16.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:28:49 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/30 19:22:26 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "42/ctype/ctype.h"
#include "42/ctype/nbr.h"

bool cstoi16(const char* str, int16_t* out) {
  if (str == NULL || out == NULL) return false;
  uint16_t value = 0;
  bool negative = false;

  while (ft_isspace(*str)) str++;
  if (*str == '+' || *str == '-') {
    if (*str == '-') negative = true;
    str++;
  }
  if (!ft_isdigit(*str)) return false;

  while (ft_isdigit(*str)) {
    uint16_t digit = (uint16_t)(*str - '0');

    value = value * 10 + digit;
    if (negative && value > (uint16_t)INT16_MAX + 1) return false;
    if (!negative && value > INT16_MAX) return false;
    str++;
  }
  while (ft_isspace(*str)) str++;
  if (*str != '\0') return false;

  if (negative) {
    *out = (int16_t)(-(int16_t)value);
  } else {
    *out = (int16_t)value;
  }
  return true;
}
