/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 21:20:46 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/30 17:41:31 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "42/alloc/string.h"

/**
 * @brief Free a string and its internal data.
 *
 * Frees the internal buffer and the t_string structure itself. Passing NULL
 * is a no-op.
 *
 * @param s Pointer to the string to free. May be NULL.
 */
void string_free(t_string* s) {
  if (s == NULL) return;
  if (!string_tagged(s)) return;

  if (s->data != NULL) free(s->data);
  s->magic = 0;
  free(s);
}
