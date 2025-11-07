/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstou64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:43:05 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 15:53:53 by lfiorell@st      ###   ########.fr       */
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

  while (ft_isspace((unsigned char)*str)) str++;
  if (*str == '+') {
    str++;
  } else if (*str == '-') {
    return false;
  }

  if (!ft_isdigit((unsigned char)*str)) return false;

  while (ft_isdigit((unsigned char)*str)) {
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
