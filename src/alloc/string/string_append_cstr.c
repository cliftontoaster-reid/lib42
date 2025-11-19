/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_append_cstr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 20:56:15 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/19 11:53:39 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "42/alloc/string.h"
#include "42/memory/cstr.h"
#include "42/memory/ops.h"

/**
 * @brief Append a C-style string to @p str.
 *
 * Appends the contents of @p cstr to the end of @p str. The function may
 * reallocate the internal buffer if needed to fit the additional data.
 *
 * @param str Pointer to the string to append to. Must not be NULL.
 * @param cstr C-style string to append. If NULL, this function behaves like
 *             appending an empty string and returns true.
 * @return true on success, false if memory allocation fails or if @p str
 *         is NULL.
 */
bool string_append_cstr(t_string* str, const char* cstr) {
  if (str == NULL) return false;
  if (cstr == NULL) return true;

  size_t cstr_len = ft_strlen(cstr);

  if (!string_reserve(str, str->size + cstr_len)) return false;

  ft_memcpy(str->data + str->size, cstr, cstr_len);
  str->size += cstr_len;
  str->data[str->size] = '\0';

  return true;
}
