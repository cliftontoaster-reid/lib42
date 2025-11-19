/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:15:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 10:16:39 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/memory/cstr.h"

size_t ft_strlcat(char* dest, const char* src, size_t size) {
  size_t dest_len = ft_strlen(dest);
  size_t src_len = ft_strlen(src);
  if (size <= dest_len) {
    return dest_len + src_len;
  }
  size_t to_copy = size - dest_len - 1;
  if (to_copy > src_len) {
    to_copy = src_len;
  }
  for (size_t i = 0; i < to_copy; i++) {
    dest[dest_len + i] = src[i];
  }
  dest[dest_len + to_copy] = '\0';
  return dest_len + src_len;
}