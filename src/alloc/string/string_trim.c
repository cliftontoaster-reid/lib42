/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_trim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:12:23 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/30 17:41:31 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/alloc/string.h"
#include "42/ctype/ctype.h"
#include "42/memory/cstr.h"

/**
 * @brief Return a new string with leading and trailing characters removed.
 *
 * Characters contained in @p chars are trimmed from the beginning and
 * end of @p s. If @p chars is NULL the function trims standard
 * whitespace characters.
 *
 * @param s Source string. Must not be NULL.
 * @param chars Set of characters to remove from both ends.
 * @return Newly allocated t_string holding the trimmed contents or NULL
 *         on allocation failure.
 * @warning This function allocates memory using malloc. The caller takes
 *          ownership of the returned t_string and must free it using
 *          string_free to avoid a memory leak.
 */
t_string* string_trim(const t_string* s, const char* chars) {
  if (s == NULL) return NULL;
  if (s->data == NULL || s->size == 0) {
    return string_new();
  }

  size_t start_trim = 0;
  size_t end_trim = s->size;
  if (chars == NULL) {
    while (start_trim < s->size && ft_isspace(s->data[start_trim])) {
      start_trim++;
    }
    while (end_trim > start_trim && ft_isspace(s->data[end_trim - 1])) {
      end_trim--;
    }
  } else {
    while (start_trim < s->size &&
           ft_strchr(chars, s->data[start_trim]) != NULL) {
      start_trim++;
    }
    while (end_trim > start_trim &&
           ft_strchr(chars, s->data[end_trim - 1]) != NULL) {
      end_trim--;
    }
  }
  if (start_trim >= end_trim) {
    return string_new();
  }
  return string_substr(s, start_trim, end_trim - start_trim);
}
