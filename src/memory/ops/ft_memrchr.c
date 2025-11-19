/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 09:10:50 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 09:10:55 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "42/memory/ops.h"

void* ft_memrchr(const void* s, int c, size_t n) {
  const unsigned char* ptr = (const unsigned char*)s;
  unsigned char byte;

  byte = (unsigned char)c;
  for (size_t i = n; i > 0; i--) {
    if (ptr[i - 1] == byte) return ((void*)(ptr + i - 1));
  }
  return (NULL);
}
