/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:15:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 10:15:51 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/memory/cstr.h"

char* ft_strcat(char* dest, const char* src) {
  size_t dest_len = ft_strlen(dest);
  size_t i = 0;
  while (src[i]) {
    dest[dest_len + i] = src[i];
    i++;
  }
  dest[dest_len + i] = '\0';
  return dest;
}