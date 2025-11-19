/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_prepend_cstr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 21:18:48 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/19 13:31:56 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "42/alloc/string.h"
#include "42/memory/cstr.h"
#include "42/memory/ops.h"

/**
 * @brief Prepend a C-style string to @p str.
 *
 * Inserts the contents of @p cstr at the beginning of the string @p str.
 * May reallocate the internal buffer to fit the new contents.
 *
 * @param str Pointer to the string to modify. Must not be NULL.
 * @param cstr C-style string to insert at beginning. If NULL, this
 *             function behaves like prepending an empty string and returns
 *             true.
 * @return true on success, false on memory allocation failure or if @p str
 *         is NULL.
 */
bool string_prepend_cstr(t_string* str, const char* cstr) {
  if (str == NULL) return false;
  if (cstr == NULL) return true;

  size_t cstr_len = ft_strlen(cstr);

  if (!string_reserve(str, str->size + cstr_len)) return false;

  ft_memmove(str->data + cstr_len, str->data, str->size);

  ft_memcpy(str->data, cstr, cstr_len);
  str->size += cstr_len;
  str->data[str->size] = '\0';

  return true;
}
