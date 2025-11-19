/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_pop_front.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 14:02:54 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "42/alloc/vec.h"
#include "42/memory/ops.h"

bool vec_pop_front(t_vec* vec) {
  if (vec->size == 0) return false;
  ft_memmove(vec->data, vec->data + vec->elem_size,
             (vec->size - 1) * vec->elem_size);
  vec->size--;
  if (vec->size < vec->capacity / 4 && vec->capacity > 1) {
    vec_resize(vec, vec->capacity / 2);
  }
  return true;
}