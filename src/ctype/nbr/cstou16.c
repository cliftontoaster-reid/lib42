/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstou16.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:39:43 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 15:54:30 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "ctype/ctype.h"
#include "ctype/nbr.h"

bool cstou16(const char* str, uint16_t* out) {
  if (str == NULL || out == NULL) return false;
  uint32_t value = 0;

  while (ft_isspace(*str)) str++;
  while (*str == '+') str++;
  if (!ft_isdigit(*str)) return false;

  while (ft_isdigit(*str)) {
    uint8_t digit = (uint8_t)(*str - '0');

    value = value * 10 + digit;
    if (value > UINT16_MAX) return false;
    str++;
  }

  *out = (uint16_t)value;
  return true;
}
