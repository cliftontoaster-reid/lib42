/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:20:12 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/29 22:26:38 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>

#include "42/alloc/string.h"

/**
 * @brief Replace a substring of @p s starting at @p pos for length @p len
 * with @p src.
 * @memberof s_string
 *
 * This is equivalent to erasing the substring and inserting @p src at
 * @p pos. The function may reallocate the buffer to accommodate the
 * resulting string.
 *
 * @param s Pointer to the string to modify. Must not be NULL.
 * @param pos Position where replacement begins.
 * @param len Length of the text to replace.
 * @param src t_string to insert in place of the erased text.
 * @return true on success, false if allocation fails, @p s is NULL, or
 *         @p pos is out of bounds.
 */
bool string_replace_string(t_string* s, size_t pos, size_t len,
                           const t_string* src) {
  if (s == NULL || src == NULL) return false;
  if (pos > s->size) return false;

  if (!string_erase(s, pos, len)) return false;
  return string_insert_string(s, pos, src);
}

/**
 * @brief Replace a substring of @p s starting at @p pos for length @p len
 * with @p cstr.
 * @memberof s_string
 *
 * This is equivalent to erasing the substring and inserting @p cstr at
 * @p pos. The function may reallocate the buffer to accommodate the
 * resulting string.
 *
 * @param s Pointer to the string to modify. Must not be NULL.
 * @param pos Position where replacement begins.
 * @param len Length of the text to replace.
 * @param cstr C-style string to insert in place of the erased text.
 * @return true on success, false if allocation fails, @p s is NULL, or
 *         @p pos is out of bounds.
 */
bool string_replace_cstr(t_string* s, size_t pos, size_t len,
                         const char* cstr) {
  if (s == NULL || cstr == NULL) return false;
  if (pos > s->size) return false;

  if (!string_erase(s, pos, len)) return false;
  return string_insert_cstr(s, pos, cstr);
}

/**
 * @brief Replace a substring of @p s starting at @p pos for length @p len
 * with @p src.
 * @memberof s_string
 *
 * This is equivalent to erasing the substring and inserting @p src at
 * @p pos. The function may reallocate the buffer to accommodate the
 * resulting string.
 *
 * @param s Pointer to the string to modify. Must not be NULL.
 * @param pos Position where replacement begins.
 * @param len Length of the text to replace.
 * @param src Pointer to the data to insert in place of the erased text.
 * @return true on success, false if allocation fails, @p s is NULL, or
 *         @p pos is out of bounds.
 */
bool string_replace(t_string* s, size_t pos, size_t len, const void* src) {
  if (s == NULL) return false;

  if (string_tagged(src)) {
    return string_replace_string(s, pos, len, (const t_string*)src);
  } else {
    return string_replace_cstr(s, pos, len, (const char*)src);
  }
}
