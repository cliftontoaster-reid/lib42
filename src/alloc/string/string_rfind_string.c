/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_rfind_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:06:15 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/19 12:31:57 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/alloc/string.h"

#include <stddef.h>

#include "42/memory/cstr.h"

/**
 * @brief Find the last occurrence of @p needle in @p s.
 *
 * @param s String to search in. Must not be NULL.
 * @param needle t_string substring to find. If needle is empty returns the
 *               last valid index (i.e. s->size).
 * @return Index of the last occurrence of @p needle, or -1 if not found.
 */
ssize_t string_rfind_string(const t_string* s, const t_string* needle) {
  if (s == NULL || needle == NULL) return -1;
  if (needle->size == 0) return s->size == 0 ? 0 : (ssize_t)s->size - 1;
  if (needle->size > s->size) return -1;
  if (needle->data == NULL || s->data == NULL) return -1;

  char* found = ft_strrstr(s->data, needle->data);
  if (found == NULL) return -1;
  return (ssize_t)(found - s->data);
}
