/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_reserve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 20:56:27 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/19 12:04:54 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>

#include "42/alloc/string.h"
#include "42/memory/ops.h"

/**
 * @brief Ensure the string has at least @p min_capacity bytes of capacity.
 *
 * If the current capacity is less than @p min_capacity, this function
 * attempts to reallocate the internal buffer to at least the requested
 * capacity. If the capacity is already sufficient, the function does
 * nothing.
 *
 * @param s Pointer to the string to modify. Must not be NULL.
 * @param min_capacity Minimum capacity to reserve.
 * @return true on success, false if reallocation fails or @p s is NULL.
 */
bool string_reserve(t_string* s, size_t min_capacity) {
  if (s == NULL) {
    return false;
  }
  if (s->capacity >= min_capacity) {
    return true;
  }

  size_t new_capacity = s->capacity;
  while (new_capacity < min_capacity) {
    new_capacity = (new_capacity == 0) ? 1 : new_capacity * 2;
  }

  if (new_capacity != s->capacity) {
    char* new_data = malloc(new_capacity + 1);
    if (new_data == NULL) {
      return false;
    }

    ft_bzero(new_data, new_capacity + 1);
    if (s->data != NULL) {
      ft_memcpy(new_data, s->data, s->size);
      new_data[s->size] = '\0';
      free(s->data);
    }

    s->data = new_data;
    s->capacity = new_capacity;
  }

  return true;
}
