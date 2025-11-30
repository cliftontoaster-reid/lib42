/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_clone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 21:29:13 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/19 11:56:28 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/alloc/string.h"

/**
 * @brief Duplicate a string.
 *
 * Allocates a new t_string and copies the contents of @p s into it.
 *
 * @param s Pointer to the source string to clone. Must not be NULL.
 * @return Pointer to a newly allocated t_string with the same contents as
 *         @p s, or NULL if allocation fails.
 * @warning This function allocates memory using malloc. The caller takes
 *          ownership of the returned t_string and must free it using
 *          string_free to avoid leaks.
 */
t_string* string_clone(const t_string* s) {
  if (s == NULL) return NULL;

  t_string* clone = string_new();
  if (clone == NULL) return NULL;

  if (!string_append_string(clone, s)) {
    string_free(clone);
    return NULL;
  }

  return clone;
}
