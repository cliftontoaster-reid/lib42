/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_push_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:55:42 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/19 12:03:48 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>

#include "42/alloc/string.h"

/**
 * @brief Append a single character to the end of the string.
 *
 * May reallocate the internal buffer to make room for the new character.
 *
 * @param s Pointer to the string to modify. Must not be NULL.
 * @param c Character to append.
 * @return true on success, false if reallocation fails or @p s is NULL.
 */
bool string_push_char(t_string* s, char c) {
  if (s == NULL) return false;

  if (!string_reserve(s, s->size + 1)) return false;

  s->data[s->size] = c;
  s->size += 1;
  s->data[s->size] = '\0';

  return true;
}
