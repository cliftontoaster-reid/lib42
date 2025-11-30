/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:19:37 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/29 22:26:56 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>

#include "42/alloc/string.h"
#include "42/memory/cstr.h"
#include "42/memory/ops.h"

/**
 * @brief Append a t_string to another t_string.
 * @memberof s_string
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
  if (src == NULL) return true;

  size_t new_size = str->size + src->size;
  if (!string_reserve(str, new_size)) return false;

  ft_memcpy(str->data + str->size, src->data, src->size);
  str->size = new_size;
  str->data[str->size] = '\0';
  return true;
}

/**
 * @brief Append a C-style string to @p str.
 * @memberof s_string
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
  if (cstr == NULL) return true;

  size_t add = ft_strlen(cstr);
  if (add == 0) return true;

  size_t new_size = str->size + add;
  if (!string_reserve(str, new_size)) return false;

  ft_memcpy(str->data + str->size, cstr, add);
  str->size = new_size;
  str->data[str->size] = '\0';
  return true;
}

/**
 * @brief Append raw data to a t_string.
 * @memberof s_string
 *
 * Appends @p src bytes to the end of @p str. The function may reallocate
 * the internal buffer if needed to fit the additional data.
 *
 * @param str Pointer to the string to append to. Must not be NULL.
 * @param src Pointer to the data to append. Must not be NULL.
 * @return true on success, false if memory allocation fails or if @p str
 *         is NULL.
 */
bool string_append(t_string* str, const void* src) {
  if (str == NULL || src == NULL) return false;

  if (string_tagged(src)) {
    return string_append_string(str, (const t_string*)src);
  } else {
    return string_append_cstr(str, (const char*)src);
  }
}
