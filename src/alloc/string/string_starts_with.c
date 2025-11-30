/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_starts_with.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:10:12 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/19 12:10:49 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/alloc/string.h"
#include "42/memory/cstr.h"

/**
 * @brief Return true if the string @p s begins with @p prefix.
 *
 * @param s Source string. Must not be NULL.
 * @param prefix C-style prefix to check. If prefix is NULL or empty
 *               the function returns true.
 * @return true if @p s starts with @p prefix, false otherwise or if @p s
 *         or @p prefix is NULL.
 */
bool string_starts_with(const t_string* s, const char* prefix) {
  if (s == NULL || prefix == NULL) return false;
  size_t prefix_len = ft_strlen(prefix);
  if (prefix_len == 0) return true;
  if (prefix_len > s->size) return false;

  return ft_strncmp(s->data, prefix, prefix_len) == 0;
}
