/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 09:11:05 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 09:11:10 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "memory/ops.h"

void* ft_memset(void* s, int c, size_t n) {
  unsigned char* ptr = (unsigned char*)s;
  unsigned char byte;

  byte = (unsigned char)c;
  for (size_t i = 0; i < n; i++) {
    ptr[i] = byte;
  }
  return (s);
}
