/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_replace_string.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 10:54:17 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/19 12:04:35 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/alloc/string.h"

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Replace a substring of @p s starting at @p pos for length @p len
 * with @p src.
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
  if (s == NULL) return false;
  if (pos > s->size) return false;
  if (src == NULL) return string_erase(s, pos, len);

  if (!string_erase(s, pos, len)) return false;
  if (!string_insert_string(s, pos, src)) return false;

  return true;
}
