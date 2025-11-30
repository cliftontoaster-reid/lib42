/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstoi64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:32:03 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/30 19:22:26 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "42/ctype/ctype.h"
#include "42/ctype/nbr.h"

bool cstoi64(const char* str, int64_t* out) {
  if (str == NULL || out == NULL) return false;
  uint64_t value = 0;
  bool negative = false;

  while (ft_isspace(*str)) str++;
  if (*str == '+' || *str == '-') {
    if (*str == '-') negative = true;
    str++;
  }
  if (!ft_isdigit(*str)) return false;

  while (ft_isdigit(*str)) {
    uint64_t digit = (uint64_t)(*str - '0');

    value = value * 10 + digit;
    if (negative && value > (uint64_t)INT64_MAX + 1) return false;
    if (!negative && value > INT64_MAX) return false;
    str++;
  }
  while (ft_isspace(*str)) str++;
  if (*str != '\0') return false;

  if (negative) {
    *out = (int64_t)(-(int64_t)value);
  } else {
    *out = (int64_t)value;
  }
  return true;
}
