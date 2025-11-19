/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_resize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:52:49 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/19 12:05:01 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>

#include "42/alloc/string.h"
#include "42/memory/ops.h"

/**
 * @brief Resize the string to @p new_size.
 *
 * If @p new_size is greater than the current size, the added bytes are
 * filled with @p fill. If @p new_size is smaller, the string is truncated.
 * The terminating NUL is updated appropriately where relevant.
 *
 * @param s Pointer to the string to modify. Must not be NULL.
 * @param new_size New desired size.
 * @param fill Character used to fill if the string grows.
 * @return true on success, false if reallocation fails or @p s is NULL.
 */
bool string_resize(t_string* s, size_t new_size, char fill) {
  if (s == NULL) return false;

  if (new_size > s->size) {
    if (!string_reserve(s, new_size)) return false;

    ft_memset(s->data + s->size, fill, new_size - s->size);
  }

  s->size = new_size;
  if (s->data != NULL) ft_bzero(s->data + s->size, s->capacity - s->size);
  string_shrink_to_fit(s);

  return true;
}
