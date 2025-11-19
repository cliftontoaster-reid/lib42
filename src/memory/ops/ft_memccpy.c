/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 09:05:54 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 09:06:44 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "42/memory/ops.h"

void* ft_memccpy(void* dest, const void* src, unsigned char c, size_t n) {
  unsigned char* d;
  const unsigned char* s;

  d = (unsigned char*)dest;
  s = (const unsigned char*)src;
  for (size_t i = 0; i < n; i++) {
    d[i] = s[i];
    if (s[i] == c) return (d + i + 1);
  }
  return (NULL);
}
