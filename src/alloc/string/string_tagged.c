/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tagged.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:24:31 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/29 16:29:40 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>

#include "42/alloc/string.h"
#include "42/memory/cstr.h"

/**
 * @brief Lightweight runtime validation of a t_string pointer.
 * @memberof s_string
 *
 * Performs a quick, non-exhaustive check to determine if @p s appears to
 * be a valid t_string created by this library.
 *
 * @param s Pointer to test.
 * @return true if @p s appears to be a valid t_string created by the
 *         library; false otherwise.
 */
bool string_tagged(const void* s) {
  if (s == NULL) return false;
  // Check the length to not read out of bounds
  size_t len = ft_strlen((const char*)s);
  if (len < sizeof(uint32_t)) return false;
  t_string *str = (t_string*)s;
  return str->magic == STRING_MAGIC;
}