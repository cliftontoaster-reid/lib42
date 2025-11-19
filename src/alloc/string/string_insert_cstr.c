/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_insert_cstr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 10:01:29 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/19 13:31:19 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>

#include "42/alloc/string.h"
#include "42/memory/cstr.h"
#include "42/memory/ops.h"

/**
 * @brief Insert a C-style string into @p s at position @p pos.
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
  if (s == NULL) return false;
  if (pos > s->size) return false;
  if (cstr == NULL) return true;

  size_t cstr_len = ft_strlen(cstr);
  if (cstr_len == 0) return true;

  if (!string_reserve(s, s->size + cstr_len)) return false;

  ft_memmove(s->data + pos + cstr_len, s->data + pos, s->size - pos);

  ft_memcpy(s->data + pos, cstr, cstr_len);
  s->size += cstr_len;
  s->data[s->size] = '\0';

  return true;
}
