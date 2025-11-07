/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_push_front.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 14:28:42 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "alloc/vec.h"
#include "memory/ops.h"

bool vec_push_front(t_vec* vec, const void* elem) {
  if (!vec || !elem) return false;
  if (vec->size == vec->capacity) {
    size_t new_cap = vec->capacity == 0 ? 1 : vec->capacity * 2;
    if (!vec_resize(vec, new_cap)) return false;
  }
  ft_memmove(vec->data + vec->elem_size, vec->data, vec->size * vec->elem_size);
  ft_memcpy(vec->data, elem, vec->elem_size);
  vec->size++;
  return true;
}