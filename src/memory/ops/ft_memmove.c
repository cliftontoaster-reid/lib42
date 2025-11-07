/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 09:07:37 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 09:07:43 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "memory/ops.h"

void* ft_memmove(void* dest, const void* src, size_t n) {
  unsigned char* d;
  const unsigned char* s;

  d = (unsigned char*)dest;
  s = (const unsigned char*)src;
  if (d < s) {
    for (size_t i = 0; i < n; i++) {
      d[i] = s[i];
    }
  } else if (d > s) {
    for (size_t i = n; i > 0; i--) {
      d[i - 1] = s[i - 1];
    }
  }
  return (dest);
}
