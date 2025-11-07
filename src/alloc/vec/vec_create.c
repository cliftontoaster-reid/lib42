/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 14:23:33 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "alloc/vec.h"

t_vec* vec_create(size_t elem_size) {
  if (elem_size == 0) {
    return NULL;
  }
  t_vec* vec = malloc(sizeof(t_vec));
  if (!vec) return NULL;
  vec->data = NULL;
  vec->size = 0;
  vec->capacity = 0;
  vec->elem_size = elem_size;
  return vec;
}
