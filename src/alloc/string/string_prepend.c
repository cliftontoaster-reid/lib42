/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_prepend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:20:06 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/29 22:26:53 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>

#include "42/alloc/string.h"
#include "42/memory/cstr.h"
#include "42/memory/ops.h"

/**
 * @brief Prepend a t_string to another t_string.
 * @memberof s_string
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
  if (src == NULL) return true;
  return string_insert_string(str, 0, src);
}

/**
 * @brief Prepend a C-style string to @p str.
 * @memberof s_string
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
  if (cstr == NULL) return true;
  return string_insert_cstr(str, 0, cstr);
}

/**
 * @brief Prepend raw data to a t_string.
 * @memberof s_string
 *
 * Inserts @p src bytes at the beginning of @p str. The function may
 * reallocate the internal buffer if needed to fit the additional data.
 *
 * @param str Pointer to the string to modify. Must not be NULL.
 * @param src Pointer to the data to prepend. Must not be NULL.
 * @return true on success, false if memory allocation fails or if @p str
 *         is NULL.
 */
bool string_prepend(t_string* str, const void* src) {
  if (str == NULL || src == NULL) return false;

  if (string_tagged(src)) {
    return string_insert_string(str, 0, (const t_string*)src);
  } else {
    return string_insert_cstr(str, 0, (const char*)src);
  }
}
