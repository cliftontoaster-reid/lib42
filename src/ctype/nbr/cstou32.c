/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstou32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:40:04 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 15:54:17 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "ctype/ctype.h"
#include "ctype/nbr.h"

bool cstou32(const char* str, uint32_t* out) {
  if (str == NULL || out == NULL) return false;
  uint64_t value = 0;

  while (ft_isspace(*str)) str++;
  while (*str == '+') str++;
  if (!ft_isdigit(*str)) return false;

  while (ft_isdigit(*str)) {
    uint8_t digit = (uint8_t)(*str - '0');

    value = value * 10 + digit;
    if (value > UINT32_MAX) return false;
    str++;
  }

  *out = (uint32_t)value;
  return true;
}
