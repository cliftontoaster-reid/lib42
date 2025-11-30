/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_ends_with.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:11:08 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/19 12:11:23 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/alloc/string.h"
#include "42/memory/cstr.h"

/**
 * @brief Return true if the string @p s ends with @p suffix.
 *
 * @param s Source string. Must not be NULL.
 * @param suffix C-style suffix to check. If suffix is NULL or empty the
 *               function returns true.
 * @return true if @p s ends with @p suffix, false otherwise or if @p s
 *         or @p suffix is NULL.
 */
bool string_ends_with(const t_string* s, const char* suffix) {
  if (s == NULL || suffix == NULL) return false;
  size_t suffix_len = ft_strlen(suffix);
  if (suffix_len == 0) return true;
  if (suffix_len > s->size) return false;

  return ft_strncmp(s->data + s->size - suffix_len, suffix, suffix_len) == 0;
}