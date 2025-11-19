/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 09:06:19 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 09:06:49 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "42/memory/ops.h"

void* ft_memchr(const void* s, int c, size_t n) {
  const unsigned char* ptr = (const unsigned char*)s;
  unsigned char byte;

  byte = (unsigned char)c;
  for (size_t i = 0; i < n; i++) {
    if (ptr[i] == byte) return ((void*)(ptr + i));
  }
  return (NULL);
}
