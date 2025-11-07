/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 09:07:24 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 10:03:20 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "memory/ops.h"

void* ft_memmem(const void* haystack, size_t haystacklen, const void* needle,
                size_t needlelen) {
  const unsigned char* h;
  const unsigned char* n;

  if (needlelen == 0) return ((void*)haystack);
  if (needlelen > haystacklen) return NULL;
  h = (const unsigned char*)haystack;
  n = (const unsigned char*)needle;
  for (size_t i = 0; i <= haystacklen - needlelen; i++) {
    if (h[i] == n[0]) {
      size_t j = 0;
      while (j < needlelen && h[i + j] == n[j]) {
        j++;
      }
      if (j == needlelen) {
        return (void*)(h + i);
      }
    }
  }
  return (NULL);
}
