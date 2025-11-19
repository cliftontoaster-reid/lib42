/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_cstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 21:36:47 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/19 12:35:34 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/alloc/string.h"

/**
 * @brief Return a pointer to the string's internal, NUL-terminated buffer.
 *
 * The returned pointer points to the internal buffer of @p s and must not
 * be freed by the caller. The pointer remains valid until the string is
 * modified or freed.
 *
 * @param s Pointer to the string. Must not be NULL.
 * @return Pointer to a NUL-terminated C string. If @p s is NULL, or if the
 *         string is empty, returns NULL.
 */
char* string_cstr(t_string* s) {
  if (s == NULL) return NULL;
  if (s->size == 0) return NULL;
  return s->data;
}
