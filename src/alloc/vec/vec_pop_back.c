/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_pop_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 14:02:28 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc/vec.h"

bool vec_pop_back(t_vec* vec) {
  if (vec->size == 0) return false;
  vec->size--;
  if (vec->size < vec->capacity / 4 && vec->capacity > 1) {
    vec_resize(vec, vec->capacity / 2);
  }
  return true;
}
