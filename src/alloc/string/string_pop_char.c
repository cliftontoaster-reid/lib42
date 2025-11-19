/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_pop_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:57:06 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/19 12:03:17 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>

#include "42/alloc/string.h"

/**
 * @brief Remove the last character from the string.
 *
 * If @p out is non-NULL, the removed character is stored at *out.
 * If the string is empty this function returns false and no character is
 * written.
 *
 * @param s Pointer to the string to modify. Must not be NULL.
 * @param out Optional output pointer to receive the removed character.
 * @return true if a character was removed, false if the string was empty
 *         or @p s is NULL.
 */
bool string_pop_char(t_string* s, char* out) {
  if (s == NULL || s->size == 0) return false;

  s->size -= 1;
  if (out != NULL) {
    *out = s->data[s->size];
  }
  s->data[s->size] = '\0';

  return true;
}
