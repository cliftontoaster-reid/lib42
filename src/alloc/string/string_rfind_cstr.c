/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_rfind_cstr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:08:23 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/19 13:32:05 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/alloc/string.h"
#include "42/memory/cstr.h"
#include "42/memory/ops.h"

/**
 * @brief Find the last occurrence of @p needle in @p s.
 *
 * @param s String to search in. Must not be NULL.
 * @param needle C-style substring to find. If needle is empty returns the
 *               last valid index (i.e. s->size).
 * @return Index of the last occurrence of @p needle, or -1 if not found.
 */
ssize_t string_rfind_cstr(const t_string* s, const char* needle) {
  if (s == NULL || needle == NULL) return -1;
  size_t needle_len = ft_strlen(needle);
  if (needle_len == 0) return (ssize_t)s->size;
  if (needle_len > s->size) return -1;

  char* found = ft_strrstr(s->data, needle);
  if (found == NULL) return -1;
  return (ssize_t)(found - s->data);
}