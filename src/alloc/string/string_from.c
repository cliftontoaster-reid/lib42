/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_from.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 20:38:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/19 12:01:07 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/alloc/string.h"
#include "42/memory/cstr.h"

/**
 * @brief Create a new string from a C-style string.
 *
 * Allocates a new t_string and copies the contents of @p cstr into the
 * internal buffer. The returned string is null-terminated.
 *
 * @param cstr Source C-string to copy. May be NULL, in which case an empty
 *             string is returned.
 * @return Pointer to a newly allocated t_string on success, or NULL if
 *         allocation fails.
 * @warning This function allocates memory using malloc. The caller takes
 *          ownership of the returned t_string and must free it using
 *          string_free to avoid a memory leak.
 */
t_string* string_from(const char* cstr) {
  t_string* str = string_new();
  if (str == NULL) return NULL;
  if (cstr == NULL) return str;

  if (!string_append_cstr(str, cstr)) {
    string_free(str);
    return NULL;
  }

  return str;
}