/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_prepend_string.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 21:13:09 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/19 12:03:35 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/alloc/string.h"

#include <stdbool.h>

#include "42/memory/ops.h"

/**
 * @brief Prepend a t_string to another t_string.
 *
 * Inserts the contents of @p src at the beginning of the string @p str.
 * May reallocate the internal buffer to fit the new contents.
 *
 * @param str Pointer to the string to modify. Must not be NULL.
 * @param src t_string to insert at beginning. If NULL, this
 *             function behaves like prepending an empty string and returns
 *             true.
 *
 * @return true on success, false on memory allocation failure or if @p str
 *         is NULL.
 */
bool string_prepend_string(t_string* str, const t_string* src) {
  if (str == NULL) return false;
  if (src == NULL || src->size == 0) return true;
  if (src->data == NULL) return false;

  if (!string_reserve(str, str->size + src->size)) return false;

  ft_memmove(str->data + src->size, str->data, str->size);

  ft_memcpy(str->data, src->data, src->size);
  str->size += src->size;
  str->data[str->size] = '\0';

  return true;
}
