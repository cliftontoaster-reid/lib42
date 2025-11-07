/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mempcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 09:10:15 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 09:10:24 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "memory/ops.h"

void* ft_mempcpy(void* dest, const void* src, size_t n) {
  unsigned char* d;
  const unsigned char* s;

  d = (unsigned char*)dest;
  s = (const unsigned char*)src;
  for (size_t i = 0; i < n; i++) {
    d[i] = s[i];
  }
  return (d + n);
}
