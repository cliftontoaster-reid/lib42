/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 21:26:53 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/19 11:54:45 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/alloc/string.h"
#include "42/memory/ops.h"

/**
 * @brief Clear the contents of the string.
 *
 * Sets the string size to zero without releasing the capacity. The buffer
 * remains allocated so further appends may reuse it.
 *
 * @warning This function does erase the contents of the string buffer by
 *         zeroing it out.
 *
 * @param s Pointer to the string to clear. Must not be NULL.
 */
void string_clear(t_string* s) {
  if (s == NULL) return;

  s->size = 0;
  if (s->data != NULL) ft_bzero(s->data, s->capacity);
}
