/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_resize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 14:28:18 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "alloc/vec.h"

bool vec_resize(t_vec* vec, size_t new_capacity) {
  if (!vec) return false;
  if (new_capacity == 0) {
    free(vec->data);
    vec->data = NULL;
    vec->capacity = 0;
    vec->size = 0;
    return true;
  }
  void* new_data = realloc(vec->data, new_capacity * vec->elem_size);
  if (!new_data) return false;
  vec->data = new_data;
  vec->capacity = new_capacity;
  if (vec->size > new_capacity) vec->size = new_capacity;
  return true;
}
