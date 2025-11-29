/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_insert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:19:51 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/29 17:46:20 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>

#include "42/alloc/string.h"
#include "42/memory/cstr.h"
#include "42/memory/ops.h"

/**
 * @brief Insert a t_string into @p s at position @p pos.
 * @memberof s_string
 * @deprecated Use \ref string_insert instead.
 *
 * Characters from @p pos onward are shifted to make room for @p src.
 * If @p pos is greater than the string size, the insertion fails and the
 * function returns false.
 *
 * @param s Pointer to the string to modify. Must not be NULL.
 * @param pos Index at which to insert. Must be <= current string size.
 * @param src t_string to insert. If NULL it is treated as empty.
 * @return true on success, false if allocation fails, @p s is NULL or
 *         @p pos is out of bounds.
 */
bool string_insert_string(t_string* s, size_t pos, const t_string* src) {
  if (s == NULL || src == NULL) return false;
  if (pos > s->size) return false;

  size_t new_size = s->size + src->size;
  if (!string_reserve(s, new_size)) return false;

  ft_memmove(s->data + pos + src->size, s->data + pos, s->size - pos);
  ft_memcpy(s->data + pos, src->data, src->size);
  s->size = new_size;
  s->data[s->size] = '\0';
  return true;
}

/**
 * @brief Insert a C-style string into @p s at position @p pos.
 * @memberof s_string
 * @deprecated Use \ref string_insert instead.
 *
 * Characters from @p pos onward are shifted to make room for @p cstr.
 * If @p pos is greater than the string size, the insertion fails and the
 * function returns false.
 *
 * @param s Pointer to the string to modify. Must not be NULL.
 * @param pos Index at which to insert. Must be <= current string size.
 * @param cstr C-style string to insert. If NULL it is treated as empty.
 * @return true on success, false if allocation fails, @p s is NULL or
 *         @p pos is out of bounds.
 */
bool string_insert_cstr(t_string* s, size_t pos, const char* cstr) {
  if (s == NULL || cstr == NULL) return false;
  if (pos > s->size) return false;

  size_t add = ft_strlen(cstr);
  if (add == 0) return true;

  size_t new_size = s->size + add;
  if (!string_reserve(s, new_size)) return false;

  ft_memmove(s->data + pos + add, s->data + pos, s->size - pos);
  ft_memcpy(s->data + pos, cstr, add);
  s->size = new_size;
  s->data[s->size] = '\0';
  return true;
}

/**
 * @brief Insert raw data into @p s at position @p pos.
 * @memberof s_string
 *
 * Characters from @p pos onward are shifted to make room for @p src.
 * If @p pos is greater than the string size, the insertion fails and the
 * function returns false.
 *
 * @param s Pointer to the string to modify. Must not be NULL.
 * @param pos Index at which to insert. Must be <= current string size.
 * @param src Pointer to the data to insert. Must not be NULL.
 * @return true on success, false if allocation fails, @p s is NULL or
 *         @p pos is out of bounds.
 */
bool string_insert(t_string* s, size_t pos, const void* src) {
  if (s == NULL || src == NULL) return false;

  if (string_tagged(src)) {
    return string_insert_string(s, pos, (const t_string*)src);
  } else {
    return string_insert_cstr(s, pos, (const char*)src);
  }
}
