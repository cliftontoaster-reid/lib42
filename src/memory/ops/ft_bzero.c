/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 09:04:41 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 09:06:47 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "42/memory/ops.h"

void ft_bzero(void* s, size_t n) {
  unsigned char* ptr = (unsigned char*)s;
  for (size_t i = 0; i < n; i++) {
    ptr[i] = 0;
  }
}
