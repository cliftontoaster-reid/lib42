/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstoi32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:29:16 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/30 19:22:26 by lfiorell         ###   ########.fr       */
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
  if (*str == '+' || *str == '-') {
    if (*str == '-') negative = true;
    str++;
  }
  if (!ft_isdigit(*str)) return false;

  while (ft_isdigit(*str)) {
    uint32_t digit = (uint32_t)(*str - '0');

    value = value * 10 + digit;
    if (negative && value > (uint32_t)INT32_MAX + 1) return false;
    if (!negative && value > INT32_MAX) return false;
    str++;
  }
  while (ft_isspace(*str)) str++;
  if (*str != '\0') return false;

  if (negative) {
    *out = (int32_t)(-(int32_t)value);
  } else {
    *out = (int32_t)value;
  }
  return true;
}
