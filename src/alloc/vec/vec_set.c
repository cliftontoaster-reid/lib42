/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 14:27:46 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "alloc/vec.h"
#include "memory/ops.h"

bool vec_set(t_vec* vec, size_t index, const void* elem) {
  if (!vec || !elem) return false;
  if (index >= vec->size) return false;
  ft_memcpy(vec->data + index * vec->elem_size, elem, vec->elem_size);
  return true;
}
