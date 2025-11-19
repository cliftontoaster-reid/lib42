/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:15:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 10:16:39 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/memory/cstr.h"

char* ft_strchr(const char* s, int c) {
  unsigned char uc = (unsigned char)c;
  size_t i = 0;
  while (s[i]) {
    if ((unsigned char)s[i] == uc) {
      return (char*)&s[i];
    }
    i++;
  }
  if (uc == '\0') {
    return (char*)&s[i];
  }
  return NULL;
}