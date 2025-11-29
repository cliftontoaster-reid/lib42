/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_find.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:19:45 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/29 16:23:48 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stddef.h>
#include <sys/types.h>

#include "42/alloc/string.h"
#include "42/memory/ops.h"

/**
 * @brief Find the first occurrence of @p needle in @p s starting at
 * position @p start.
 * @memberof s_string
 * @deprecated Use \ref string_find instead.
 *
 * @param s String to search in. Must not be NULL.
 * @param needle t_string substring to find. If needle is empty returns @p
 *               start.
 * @param start Index from where the search should begin.
 * @return Index of the first occurrence of @p needle at or after @p start,
 *         or -1 if not found. Returns -1 if @p s or @p needle is NULL.
 */
ssize_t string_find_string(const t_string* s, const t_string* needle, size_t start) {
  if (s == NULL || needle == NULL) return -1;
  if (needle->size == 0) return (start <= s->size) ? (ssize_t)start : -1;
  if (needle->size > s->size) return -1;

  for (size_t i = start; i <= s->size - needle->size; i++) {
    if (ft_memcmp(s->data + i, needle->data, needle->size) == 0) {
      return (ssize_t)i;
    }
  }
  return -1;
}

/**
 * @brief Find the first occurrence of @p needle in @p s starting at
 * position @p start.
 * @memberof s_string
 * @deprecated Use \ref string_find instead.
 *
 * @param s String to search in. Must not be NULL.
 * @param needle C-style substring to find. If needle is empty returns @p
 *               start.
 * @param start Index from where the search should begin.
 * @return Index of the first occurrence of @p needle at or after @p start,
 *         or -1 if not found. Returns -1 if @p s or @p needle is NULL.
 */
ssize_t string_find_cstr(const t_string* s, const char* needle, size_t start) {
  if (s == NULL || needle == NULL) return -1;
  size_t needle_len = 0;
  while (needle[needle_len] != '\0') {
    needle_len++;
  }
  if (needle_len == 0) return (start <= s->size) ? (ssize_t)start : -1;
  if (needle_len > s->size) return -1;

  for (size_t i = start; i <= s->size - needle_len; i++) {
    if (ft_memcmp(s->data + i, needle, needle_len) == 0) {
      return (ssize_t)i;
    }
  }
  return -1;
}

/**
 * @brief Find the first occurrence of @p needle in @p s starting at
 * position @p start.
 * @memberof s_string
 *
 * @param s String to search in. Must not be NULL.
 * @param needle Pointer to the data to find. Must not be NULL.
 * @param start Index from where the search should begin.
 * @return Index of the first occurrence of @p needle at or after @p start,
 *         or -1 if not found. Returns -1 if @p s or @p needle is NULL.
 */
ssize_t string_find(const t_string* s, const void* needle, size_t start) {
  if (s == NULL || needle == NULL) return -1;

  if (string_tagged(needle)) {
    return string_find_string(s, (const t_string*)needle, start);
  } else {
    return string_find_cstr(s, (const char*)needle, start);
  }
}
