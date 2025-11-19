/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_replace_cstr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 10:57:57 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/19 13:27:44 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>

#include "42/alloc/string.h"

/**
 * @brief Replace a substring of @p s starting at @p pos for length @p len
 * with @p cstr.
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
  if (s == NULL) return false;
  if (pos > s->size) return false;
  if (cstr == NULL) return string_erase(s, pos, len);

  if (!string_erase(s, pos, len)) return false;
  if (!string_insert_cstr(s, pos, cstr)) return false;

  return true;
}
