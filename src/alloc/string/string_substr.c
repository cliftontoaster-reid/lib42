/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_substr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 11:00:25 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/19 11:01:32 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "42/alloc/string.h"
#include "42/memory/ops.h"

/**
 * @brief Create a new string containing a substring of @p s.
 *
 * Allocates a new t_string containing a copy of the substring starting
 * at @p pos and up to @p len bytes. If @p pos is out of bounds this
 * function returns NULL. If @p pos + @p len exceeds the string size the
 * substring is truncated to the end of the string.
 *
 * @param s Source string.
 * @param pos Starting index for the substring.
 * @param len Maximum length of the substring.
 * @return Pointer to a newly allocated t_string holding the substring or
 *         NULL if allocation fails or if @p pos is out of bounds.
 * @warning This function allocates memory using malloc. The caller takes
 *          ownership of the returned t_string and must free it using
 *          string_free to avoid a memory leak.
 */
t_string* string_substr(const t_string* s, size_t pos, size_t len) {
  if (s == NULL) return NULL;
  if (pos >= s->size) return NULL;

  size_t substr_len = len;
  if (pos + len > s->size) {
    substr_len = s->size - pos;
  }

  t_string* substr = string_new();
  if (substr == NULL) return NULL;

  if (!string_reserve(substr, substr_len)) {
    string_free(substr);
    return NULL;
  }

  ft_memcpy(substr->data, s->data + pos, substr_len);
  substr->size = substr_len;
  substr->data[substr->size] = '\0';

  return substr;
}
