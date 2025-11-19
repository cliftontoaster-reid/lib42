/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 09:07:13 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 09:07:18 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "42/memory/ops.h"

void* ft_memcpy(void* dest, const void* src, size_t n) {
  unsigned char* d;
  const unsigned char* s;

  d = (unsigned char*)dest;
  s = (const unsigned char*)src;
  for (size_t i = 0; i < n; i++) {
    d[i] = s[i];
  }
  return (dest);
}
