/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_shrink_to_fit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 08:37:35 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/19 12:05:11 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>

#include "42/alloc/string.h"
#include "42/memory/ops.h"

/**
 * @brief Shrink the string's capacity to fit its size.
 *
 * Attempts to reduce the string's capacity to the current size (plus the
 * terminating NUL if applicable) to free unused memory. May reallocate the
 * internal buffer.
 *
 * @param s Pointer to the string to shrink. Must not be NULL.
 * @return true on success or if no shrink is needed, false on allocation
 *         failure.
 */
bool string_shrink_to_fit(t_string* s) {
  if (s == NULL) return false;
  if (s->data == NULL) return true;

  size_t new_capacity = 1;

  while (new_capacity < s->size + 1) {
    new_capacity *= 2;
  }

  if (new_capacity < s->capacity) {
    char* new_data = malloc(new_capacity);
    if (new_data == NULL) return false;

    ft_memcpy(new_data, s->data, s->size);
    new_data[s->size] = '\0';
    free(s->data);

    s->data = new_data;
    s->capacity = new_capacity;
  }

  return true;
}
