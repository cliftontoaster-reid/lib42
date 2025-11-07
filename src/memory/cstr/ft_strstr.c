/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:15:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 10:16:39 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory/cstr.h"

char* ft_strstr(const char* haystack, const char* needle) {
  if (!*needle) return (char*)haystack;
  size_t needle_len = ft_strlen(needle);
  size_t i = 0;
  while (haystack[i]) {
    if (ft_strncmp(&haystack[i], needle, needle_len) == 0) {
      return (char*)&haystack[i];
    }
    i++;
  }
  return NULL;
}