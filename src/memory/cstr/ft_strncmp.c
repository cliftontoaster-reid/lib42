/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:15:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 10:16:39 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/memory/cstr.h"

int ft_strncmp(const char* s1, const char* s2, size_t n) {
  if (n == 0) return 0;
  size_t i = 0;
  while (i < n && s1[i] && s2[i]) {
    if (s1[i] != s2[i]) {
      return (unsigned char)s1[i] - (unsigned char)s2[i];
    }
    i++;
  }
  if (i < n) {
    return (unsigned char)s1[i] - (unsigned char)s2[i];
  }
  return 0;
}