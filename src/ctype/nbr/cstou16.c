/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstou16.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:39:43 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/30 19:22:26 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "42/ctype/ctype.h"
#include "42/ctype/nbr.h"

bool cstou16(const char* str, uint16_t* out) {
  if (str == NULL || out == NULL) return false;
  uint32_t value = 0;

  while (ft_isspace(*str)) str++;
  if (*str == '+')
    str++;
  else if (*str == '-')
    return false;
  if (!ft_isdigit(*str)) return false;

  while (ft_isdigit(*str)) {
    uint8_t digit = (uint8_t)(*str - '0');

    value = value * 10 + digit;
    if (value > UINT16_MAX) return false;
    str++;
  }
  while (ft_isspace(*str)) str++;
  if (*str != '\0') return false;

  *out = (uint16_t)value;
  return true;
}
