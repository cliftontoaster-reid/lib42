/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstoi8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:23:52 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/30 19:22:26 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/ctype/ctype.h"
#include "42/ctype/nbr.h"

bool cstoi8(const char* str, int8_t* out) {
  if (str == NULL || out == NULL) return false;
  uint8_t value = 0;
  bool negative = false;

  while (ft_isspace(*str)) str++;
  if (*str == '+' || *str == '-') {
    if (*str == '-') negative = true;
    str++;
  }
  if (!ft_isdigit(*str)) return false;

  while (ft_isdigit(*str)) {
    uint8_t digit = (uint8_t)(*str - '0');

    value = value * 10 + digit;
    if (negative && value > (uint8_t)INT8_MAX + 1) return false;
    if (!negative && value > INT8_MAX) return false;
    str++;
  }
  while (ft_isspace(*str)) str++;
  if (*str != '\0') return false;

  if (negative) {
    *out = (int8_t)(-(int8_t)value);
  } else {
    *out = (int8_t)value;
  }
  return true;
}
