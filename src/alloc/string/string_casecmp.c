/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_casecmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:40:46 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/29 17:13:32 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "42/alloc/string.h"
#include "42/ctype/ctype.h"

/**
 * @brief Case-insensitive lexicographic comparison of two strings.
 * @memberof s_string
 *
 * Similar to string_cmp but treats characters case-insensitively.
 *
 * @param a First string.
 * @param b Second string.
 * @return Negative value if a < b, zero if a == b, positive value if
 *         a > b when compared case-insensitively.
 */
int string_casecmp(const t_string* a, const t_string* b) {
  if (a == NULL && b == NULL) return 0;
  if (a == NULL) return -1;
  if (b == NULL) return 1;

  size_t min_size = (a->size < b->size) ? a->size : b->size;
  for (size_t i = 0; i < min_size; ++i) {
    unsigned char c1 = (unsigned char)a->data[i];
    unsigned char c2 = (unsigned char)b->data[i];
    int diff = (int)ft_tolower(c1) - (int)ft_tolower(c2);
    if (diff != 0) return diff;
  }

  if (a->size < b->size) return -1;
  if (a->size > b->size) return 1;

  return 0;
}
