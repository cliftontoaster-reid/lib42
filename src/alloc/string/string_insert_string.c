/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_insert_string.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:59:06 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/19 13:31:33 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/alloc/string.h"

#include <stdbool.h>
#include <stddef.h>

#include "42/memory/ops.h"

/**
 * @brief Insert a t_string into @p s at position @p pos.
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
  if (s == NULL) return false;
  if (pos > s->size) return false;
  if (src == NULL || src->size == 0) return true;
  if (src->data == NULL) return false;

  if (!string_reserve(s, s->size + src->size)) return false;

  ft_memmove(s->data + pos + src->size, s->data + pos, s->size - pos);

  ft_memcpy(s->data + pos, src->data, src->size);
  s->size += src->size;
  s->data[s->size] = '\0';

  return true;
}
