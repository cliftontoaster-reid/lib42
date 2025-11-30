/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_erase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 10:29:12 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/30 17:41:31 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>

#include "42/alloc/string.h"
#include "42/memory/ops.h"

/**
 * @brief Erase a substring from @p s starting at @p pos of length @p len.
 *
 * Characters following the erased segment are shifted left to fill the
 * gap. If @p pos is out of bounds this returns false. If @p pos + @p len
 * goes beyond the end of the string, the function erases up to the end
 * of the string.
 *
 * @param s Pointer to the string to modify. Must not be NULL.
 * @param pos Position to begin erasing.
 * @param len Number of bytes to erase.
 * @return true on success, false if @p s is NULL or @p pos is out of
 *         bounds.
 */
bool string_erase(t_string* s, size_t pos, size_t len) {
  if (s == NULL) return false;
  if (pos >= s->size) return false;

  size_t actual_len = len;
  if (pos + len >= s->size) {
    actual_len = s->size - pos;
  }

  if (pos + len >= s->size) {
    // Erase to end - just zero the bytes we're removing and update size
    ft_bzero(s->data + pos, actual_len);
    s->size = pos;
    s->data[s->size] = '\0';
    return true;
  }

  ft_memmove(s->data + pos, s->data + pos + len, s->size - (pos + len));
  s->size -= len;
  ft_bzero(s->data + s->size, len);
  s->data[s->size] = '\0';

  return true;
}
