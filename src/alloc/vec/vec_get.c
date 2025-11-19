/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 14:29:14 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/alloc/vec.h"

void* vec_get(const t_vec* vec, size_t index) {
  if (!vec) return NULL;
  if (index >= vec->size) return NULL;
  return vec->data + index * vec->elem_size;
}
