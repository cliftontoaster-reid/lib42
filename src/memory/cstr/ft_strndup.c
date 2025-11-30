/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:15:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 10:16:39 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "42/memory/cstr.h"

char* ft_strndup(const char* s, size_t n) {
  size_t len = 0;
  while (len < n && s[len]) len++;
  char* dup = (char*)malloc(len + 1);
  if (!dup) return NULL;
  for (size_t i = 0; i < len; i++) {
    dup[i] = s[i];
  }
  dup[len] = '\0';
  return dup;
}