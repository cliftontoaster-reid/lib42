/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstou32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:40:04 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/30 19:22:26 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "42/ctype/ctype.h"
#include "42/ctype/nbr.h"

bool cstou32(const char* str, uint32_t* out) {
  if (str == NULL || out == NULL) return false;
  uint64_t value = 0;

  while (ft_isspace(*str)) str++;
  if (*str == '+')
    str++;
  else if (*str == '-')
    return false;
  if (!ft_isdigit(*str)) return false;

  while (ft_isdigit(*str)) {
    uint8_t digit = (uint8_t)(*str - '0');

    value = value * 10 + digit;
    if (value > UINT32_MAX) return false;
    str++;
  }
  while (ft_isspace(*str)) str++;
  if (*str != '\0') return false;

  *out = (uint32_t)value;
  return true;
}
