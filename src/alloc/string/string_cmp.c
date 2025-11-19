/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_cmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 21:33:38 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/19 11:57:54 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/alloc/string.h"
#include "42/memory/ops.h"

/**
 * @brief Compare two strings lexicographically.
 *
 * Returns an integer less than, equal to, or greater than zero if @p a is
 * found, respectively, to be less than, to match, or be greater than
 * @p b.
 *
 * @param a First string to compare.
 * @param b Second string to compare.
 * @return Negative value if a < b, zero if a == b, positive value if
 *         a > b.
 */
int string_cmp(const t_string* a, const t_string* b) {
  if (a == NULL && b == NULL) return 0;
  if (a == NULL) return -1;
  if (b == NULL) return 1;

  size_t min_size = (a->size < b->size) ? a->size : b->size;
  int cmp_result = ft_memcmp(a->data, b->data, min_size);
  if (cmp_result != 0) return cmp_result;

  if (a->size < b->size) return -1;
  if (a->size > b->size) return 1;

  return 0;
}
