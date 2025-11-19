/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_append_string.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 21:05:52 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/19 11:53:54 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/alloc/string.h"

#include <stdbool.h>
#include <stdlib.h>

#include "42/memory/ops.h"

/**
 * @brief Append a t_string to another t_string.
 *
 * This function appends all bytes of @p src to the end of @p str.
 * It behaves like `string_append(dest, src->data)` but is provided
 * for clarity and to handle the case where src and dest are the
 * same object.
 *
 * @param str Pointer to the string to append to. Must not be NULL.
 * @param src t_string to append. If NULL, this function behaves like
 *             appending an empty string and returns true.
 * @return true on success, false on memory allocation failure or if @p str
 *         is NULL.
 */
bool string_append_string(t_string* str, const t_string* src) {
  if (str == NULL) return false;
  if (src == NULL || src->size == 0) return true;
  if (src->data == NULL) return false;

  if (!string_reserve(str, str->size + src->size)) return false;

  ft_memcpy(str->data + str->size, src->data, src->size);
  str->size += src->size;
  str->data[str->size] = '\0';

  return true;
}
