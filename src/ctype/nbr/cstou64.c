/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstou64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:43:05 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/30 19:22:26 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stddef.h>
#include <stdint.h>

#include "42/ctype/ctype.h"
#include "42/ctype/nbr.h"

bool cstou64(const char* str, uint64_t* out) {
  if (str == NULL || out == NULL) return false;
  uint64_t value = 0;

  while (ft_isspace(*str)) str++;
  if (*str == '+') {
    str++;
  } else if (*str == '-') {
    return false;
  }

  if (!ft_isdigit(*str)) return false;

  while (ft_isdigit(*str)) {
    uint8_t digit = (uint8_t)(*str - '0');

    if (value > UINT64_MAX / 10 ||
        (value == UINT64_MAX / 10 && digit > (uint8_t)(UINT64_MAX % 10)))
      return false;
    value = value * 10 + digit;
    str++;
  }
  while (ft_isspace(*str)) str++;
  if (*str != '\0') return false;

  *out = value;
  return true;
}
