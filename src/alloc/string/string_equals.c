/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_equals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:14:35 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/19 13:29:56 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/alloc/string.h"
#include "42/memory/cstr.h"
#include "42/memory/ops.h"

/**
 * @brief Return true if two strings are exactly equal.
 *
 * @param a First string.
 * @param b Second string.
 * @return true if both strings have the same size and identical contents,
 *         false otherwise.
 */
bool string_equals(const t_string* a, const t_string* b) {
  if (a == NULL || b == NULL) return false;
  if (a->size != b->size) return false;
  if (a->data == NULL || b->data == NULL) return false;

  return ft_memcmp(a->data, b->data, a->size) == 0;
}
