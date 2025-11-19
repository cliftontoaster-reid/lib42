/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstounbr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:56:01 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 15:56:20 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "42/ctype/ctype.h"
#include "42/ctype/nbr.h"

bool cstounbr(const char* str, unsigned int* out) {
  if (str == NULL || out == NULL) return false;
  unsigned int value = 0;

  while (ft_isspace(*str)) str++;
  while (*str == '+') str++;
  if (!ft_isdigit(*str)) return false;

  while (ft_isdigit(*str)) {
    unsigned int digit = (unsigned int)(*str - '0');

    if (value > UINT_MAX / 10 ||
        (value == UINT_MAX / 10 && digit > (unsigned int)(UINT_MAX % 10)))
      return false;
    value = value * 10 + digit;
    str++;
  }

  *out = value;
  return true;
}
