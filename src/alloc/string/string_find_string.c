/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_find_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 11:41:48 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/19 11:52:39 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/alloc/string.h"

#include <stddef.h>
#include <sys/types.h>

#include "42/memory/cstr.h"

/**
 * @brief Find the first occurrence of @p needle in @p s starting at
 * position @p start.
 *
 * @param s String to search in. Must not be NULL.
 * @param needle t_string substring to find. If needle is empty returns @p
 *               start.
 * @param start Index from where the search should begin.
 * @return Index of the first occurrence of @p needle at or after @p start,
 *         or -1 if not found. Returns -1 if @p s or @p needle is NULL.
 */
ssize_t string_find_string(const t_string* s, const t_string* needle,
                           size_t start) {
  if (s == NULL || needle == NULL) return -1;
  if (start >= s->size) return -1;
  if (needle->size == 0) return (ssize_t)start;
  if (needle->size > s->size) return -1;
  if (needle->data == NULL || s->data == NULL) return -1;

  char* found = ft_strstr(s->data + start, needle->data);
  if (found == NULL) return -1;
  return (ssize_t)(found - s->data);
}
