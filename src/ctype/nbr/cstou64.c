/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstou64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:43:05 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 17:00:08 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stddef.h>
#include <stdint.h>

#include "ctype/ctype.h"
#include "ctype/nbr.h"

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

  *out = value;
  return true;
}
