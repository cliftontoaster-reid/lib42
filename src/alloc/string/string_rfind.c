/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_rfind.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:20:17 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/29 22:26:37 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <sys/types.h>

#include "42/alloc/string.h"
#include "42/memory/cstr.h"

/**
 * @brief Find the last occurrence of @p needle in @p s.
 * @memberof s_string
 *
 * @param s String to search in. Must not be NULL.
 * @param needle t_string substring to find. If needle is empty returns the
 *               last valid index (i.e. s->size).
 * @return Index of the last occurrence of @p needle, or -1 if not found.
 */
ssize_t string_rfind_string(const t_string* s, const t_string* needle) {
  if (s == NULL || needle == NULL) return -1;

  if (needle->size == 0) {
    return (ssize_t)s->size;
  }
  if (needle->size > s->size) {
    return -1;
  }

  for (ssize_t i = (ssize_t)(s->size - needle->size); i >= 0; --i) {
    if (ft_strncmp(s->data + i, needle->data, needle->size) == 0) {
      return i;
    }
  }
  return -1;
}

/**
 * @brief Find the last occurrence of @p needle in @p s.
 * @memberof s_string
 *
 * @param s String to search in. Must not be NULL.
 * @param needle C-style substring to find. If needle is empty returns the
 *               last valid index (i.e. s->size).
 * @return Index of the last occurrence of @p needle, or -1 if not found.
 */
ssize_t string_rfind_cstr(const t_string* s, const char* needle) {
  if (s == NULL || needle == NULL) return -1;

  size_t needle_len = ft_strlen(needle);
  if (needle_len == 0) {
    return (ssize_t)s->size;
  }
  if (needle_len > s->size) {
    return -1;
  }

  for (ssize_t i = (ssize_t)(s->size - needle_len); i >= 0; --i) {
    if (ft_strncmp(s->data + i, needle, needle_len) == 0) {
      return i;
    }
  }
  return -1;
}

/**
 * @brief Find the last occurrence of @p needle in @p s.
 * @memberof s_string
 *
 * @param s String to search in. Must not be NULL.
 * @param needle Pointer to the data to find. Must not be NULL.
 * @return Index of the last occurrence of @p needle, or -1 if not found.
 */
ssize_t string_rfind(const t_string* s, const void* needle) {
  if (s == NULL || needle == NULL) return -1;

  if (string_tagged(needle)) {
    return string_rfind_string(s, (const t_string*)needle);
  } else {
    return string_rfind_cstr(s, (const char*)needle);
  }
}
