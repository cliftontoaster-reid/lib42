/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 09:06:58 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 09:07:04 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "memory/ops.h"

int ft_memcmp(const void* s1, const void* s2, size_t n) {
  const unsigned char* ptr1 = (const unsigned char*)s1;
  const unsigned char* ptr2 = (const unsigned char*)s2;

  for (size_t i = 0; i < n; i++) {
    if (ptr1[i] != ptr2[i]) {
      return (ptr1[i] - ptr2[i]);
    }
  }
  return (0);
}
